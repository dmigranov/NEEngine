#include "pch.h"
#include "SphericalExpFogPointEffect.h"

#include "Game.h"

#include "CircleGeometryShader.h" // generated from BasicPixelShader.hlsl


SphericalExpFogPointEffect::SphericalExpFogPointEffect(double fogDensity, DirectX::XMVECTORF32 fogColor) : SphericalExpFogEffect(nullptr, fogDensity, fogColor)
{
	m_magic = "SphericalExpFogPoint";
	Initialize(); //parent Initialize already called
}

bool SphericalExpFogPointEffect::Initialize()
{
	g_d3dGeometryShader = game.CreateGeometryShaderFromBytecode(g_cgs, sizeof(g_cgs));

	//todo: constant buffer for circles radiuses

	return true;
}

void SphericalExpFogPointEffect::Deinitialize()
{
	SphericalExpFogEffect::Deinitialize();

	SafeRelease(g_d3dGeometryShader);
}

void SphericalExpFogPointEffect::UpdatePerObject(const Entity* pEntity)
{
	SphericalExpFogEffect::UpdatePerObject(pEntity);

	game.GSSetShader(g_d3dGeometryShader);
}

void SphericalExpFogPointEffect::Clean()
{
	game.GSSetShader(nullptr);
}
