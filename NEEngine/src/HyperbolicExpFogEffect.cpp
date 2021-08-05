#include "pch.h"
#include "HyperbolicExpFogEffect.h"
#include "Texture.h"
#include "Scene.h"


#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

HyperbolicExpFogEffect::HyperbolicExpFogEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor)
{
	m_magic = "HyperbolicExpFog";
	m_pTexture = pTexture;
	perApplicationVSConstantBuffer.density = fogDensity;
	perApplicationPSConstantBuffer.fogColor = fogColor;
	Initialize();
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
