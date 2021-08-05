#include "pch.h"
#include "HyperbolicExpFogEffect.h"
#include "Texture.h"
#include "Scene.h"

#include "HyperbolicMeshComponentFactory.h"	//для импорта структуры


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
	//g_d3dVertexShader = game.CreateVertexShaderFromBytecode(///////////); //todo
	g_d3dPixelShader = game.CreatePixelShaderFromBytecode(g_ps, sizeof(g_ps));

	return false;
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
