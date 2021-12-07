#include "pch.h"
#include "SphericalDopplerEffect.h"
#include "Texture.h"
#include "Scene.h"

#include "SphericalMeshComponentFactory.h"	//для импорта структуры

#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"
#include "Entity.h"

#include "Game.h"

SphericalDopplerEffect::SphericalDopplerEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor) : SphericalExpFogEffect(pTexture, fogDensity, fogColor)
{
	m_magic = "SphericalExpFogPoint";
	Initialize(); //parent Initialize already called
}
