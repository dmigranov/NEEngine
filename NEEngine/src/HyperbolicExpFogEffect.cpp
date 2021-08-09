#include "pch.h"
#include "HyperbolicExpFogEffect.h"
#include "Texture.h"
#include "Scene.h"

#include "HyperbolicMeshComponentFactory.h"	//äëÿ èìïîðòà ñòðóêòóðû

#include "HyperbolicTransformComponent.h"
#include "HyperbolicCameraComponent.h"
#include "Entity.h"

#include "Game.h"

//#include "HypExpVertexShader.h"
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
	//g_d3dVertexShader = game.CreateVertexShaderFromBytecode(g_hypexpvs, sizeof(g_hypexpvs)); //TODO: ÐÀÑÑÊÎÌÅÍÒÈÐÎÂÀÒÜ
	g_d3dPixelShader = game.CreatePixelShaderFromBytecode(g_ps, sizeof(g_ps));

	//input assembly:
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(HyperbolicMeshComponentFactory::VertexData, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//Once an input-layout object is created from a shader signature, the input-layout object can be reused with any other shader that has an identical input signature (semantics included). 
	//g_d3dInputLayout = game.CreateInputLayout(vertexLayoutDesc, _countof(vertexLayoutDesc), g_hypexpvs, sizeof(g_hypexpvs)); //TODO: ÐÀÑÑÊÎÌÅÍÒÈÐÎÂÀÒÜ

	//buffers:
	//todo


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

void HyperbolicExpFogEffect::UpdatePerObject(const Entity* pEntity)
{
	auto pSphCameraComponent = game.GetScene()->GetCamera()->GetComponent<HyperbolicCameraComponent>();
	perApplicationVSConstantBuffer.proj = pSphCameraComponent->GetProj();
	game.UpdateSubresource(g_d3dVSConstantBuffers[ConstantBuffer::CB_Application], &perApplicationVSConstantBuffer);
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
