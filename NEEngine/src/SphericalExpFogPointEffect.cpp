#include "pch.h"
#include "SphericalExpFogPointEffect.h"

#include "Game.h"

#include "GeometryShader.h" // generated from BasicPixelShader.hlsl


SphericalExpFogPointEffect::SphericalExpFogPointEffect(double fogDensity, DirectX::XMVECTORF32 fogColor) : SphericalExpFogEffect(nullptr, fogDensity, fogColor)
{
	m_magic = "SphericalExpFogPoint";
	Initialize(); //parent Initialize already called
}

bool SphericalExpFogPointEffect::Initialize()
{
	g_d3dGeometryShader = game.CreateGeometryShaderFromBytecode(g_gs, sizeof(g_gs));

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
}

void SphericalExpFogPointEffect::Clean()
{
}
