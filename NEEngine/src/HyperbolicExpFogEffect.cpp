#include "pch.h"
#include "HyperbolicExpFogEffect.h"
#include "Texture.h"
#include "Scene.h"

#include "HyperbolicMeshComponentFactory.h"	//для импорта структуры

#include "HyperbolicTransformComponent.h"
#include "HyperbolicCameraComponent.h"
#include "Entity.h"

#include "Game.h"

#include "HypExpVertexShader.h"
#include "PixelShader.h" // generated from BasicPixelShader.hlsl

using namespace DirectX;
using namespace DirectX::SimpleMath;

HyperbolicExpFogEffect::HyperbolicExpFogEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor) : game(Game::GetInstance())
{
	m_magic = "HyperbolicExpFog";
	m_pTexture = pTexture;
	perApplicationVSConstantBuffer.density = fogDensity;
	perApplicationPSConstantBuffer.fogColor = fogColor;
	Initialize();
}

bool HyperbolicExpFogEffect::Initialize()
{
	// shaders
	// vertex shaders have to have the same signature
	g_d3dVertexShader = game.CreateVertexShaderFromBytecode(g_hypexpvs, sizeof(g_hypexpvs)); 
	g_d3dPixelShader = game.CreatePixelShaderFromBytecode(g_ps, sizeof(g_ps));

	//input assembly:
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(HyperbolicMeshComponentFactory::VertexData, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//Once an input-layout object is created from a shader signature, the input-layout object can be reused with any other shader that has an identical input signature (semantics included). 
	g_d3dInputLayout = game.CreateInputLayout(vertexLayoutDesc, _countof(vertexLayoutDesc), g_hypexpvs, sizeof(g_hypexpvs)); 

	//buffers:
	D3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	constantBufferDesc.ByteWidth = sizeof(PerObjectVSConstantBuffer);
	g_d3dVSConstantBuffers[CB_Object] = game.CreateBuffer(constantBufferDesc);

	constantBufferDesc.ByteWidth = sizeof(PerFrameVSConstantBuffer);
	g_d3dVSConstantBuffers[CB_Frame] = game.CreateBuffer(constantBufferDesc);

	constantBufferDesc.ByteWidth = sizeof(PerApplicationVSConstantBuffer);
	g_d3dVSConstantBuffers[CB_Application] = game.CreateBuffer(constantBufferDesc);


	constantBufferDesc.ByteWidth = sizeof(PerApplicationPSConstantBuffer);
	g_d3dPSConstantBuffer = game.CreateBuffer(constantBufferDesc);

	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);

	//sampler (for texture)
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	g_d3dSamplerState = game.CreateSamplerState(samplerDesc);

	return true;
}

void HyperbolicExpFogEffect::Deinitialize()
{
	SafeRelease(g_d3dVSConstantBuffers[CB_Application]);
	SafeRelease(g_d3dVSConstantBuffers[CB_Frame]);
	SafeRelease(g_d3dVSConstantBuffers[CB_Object]);
	SafeRelease(g_d3dPSConstantBuffer);

	SafeRelease(g_d3dSamplerState);

	SafeRelease(g_d3dInputLayout);

	SafeRelease(g_d3dVertexShader);
	SafeRelease(g_d3dPixelShader);
}

void HyperbolicExpFogEffect::UpdatePerObject(const Entity* pEntity, double deltaTime)
{
	auto pSphCameraComponent = game.GetScene()->GetCamera()->GetComponent<HyperbolicCameraComponent>();
	perApplicationVSConstantBuffer.proj = pSphCameraComponent->GetProj();
	game.UpdateSubresource(g_d3dVSConstantBuffers[ConstantBuffer::CB_Application], &perApplicationVSConstantBuffer);

	const auto& view = game.GetScene()->GetCamera()->GetComponent<HyperbolicTransformComponent>()->GetView();
	game.UpdateSubresource(g_d3dVSConstantBuffers[ConstantBuffer::CB_Frame], &view);

	HyperbolicTransformComponent* pTransformComponent = pEntity->GetComponent<HyperbolicTransformComponent>();
	const auto& world = pTransformComponent->GetWorld();
	game.UpdateSubresource(g_d3dVSConstantBuffers[ConstantBuffer::CB_Object], &world);

	//TODO: update the three subresourses simultaneously (by providing an array)

	//input assembly stage
	game.IASetInputLayout(g_d3dInputLayout);

	//vertex shader stage
	game.VSSetShader(g_d3dVertexShader);
	game.VSSetConstantBuffers(3, g_d3dVSConstantBuffers);

	//pixel shader stage
	game.PSSetSampler(g_d3dSamplerState);
	game.PSSetShader(g_d3dPixelShader);
	if (m_pTexture != nullptr)
	{     //Pixel Shader Stafe - unique 4 every stage
		auto shaderResource = m_pTexture->GetTexture();
		game.PSSetShaderResources(1, &shaderResource);
	}
	game.PSSetConstantBuffers(1, &g_d3dPSConstantBuffer);
}

void HyperbolicExpFogEffect::UpdatePerScene()
{
	//todo
}

void HyperbolicExpFogEffect::UpdatePerApplication()
{
	//todo
}

unsigned int HyperbolicExpFogEffect::GetVertexBufferSize() const
{
	return sizeof(HyperbolicMeshComponentFactory::VertexData);
}

const std::type_info& HyperbolicExpFogEffect::GetVertexDataType()
{
	return typeid(HyperbolicMeshComponentFactory::VertexData);
}

void HyperbolicExpFogEffect::SetFogColor(DirectX::XMVECTORF32 fogColor)
{
	perApplicationPSConstantBuffer.fogColor = fogColor;
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);
}

HyperbolicExpFogEffect::~HyperbolicExpFogEffect()
{
	Deinitialize();
}