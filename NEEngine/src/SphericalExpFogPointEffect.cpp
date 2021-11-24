#include "pch.h"
#include "SphericalExpFogPointEffect.h"

SphericalExpFogPointEffect::SphericalExpFogPointEffect(double fogDensity, DirectX::XMVECTORF32 fogColor) : SphericalExpFogEffect(nullptr, fogDensity, fogColor)
{
	m_magic = "SphericalExpFogPoint";
	Initialize(); //parent Initialize already called
}

bool SphericalExpFogPointEffect::Initialize()
{
	return false;
}

void SphericalExpFogPointEffect::Deinitialize()
{
}

void SphericalExpFogPointEffect::UpdatePerObject(const Entity* pEntity)
{
}

void SphericalExpFogPointEffect::Clean()
{
}
