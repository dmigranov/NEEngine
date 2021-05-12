#include "pch.h"
#include "ToricExpFogEffect.h"

#include "Texture.h"
#include "Scene.h"

#include "EuclideanMeshComponentFactory.h"	//для импорта структуры

#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"
#include "Entity.h"

#include "Game.h"

//todo: include shaders 

using namespace DirectX;
using namespace DirectX::SimpleMath;

ToricExpFogEffect::ToricExpFogEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor) : game(Game::GetInstance())
{
	m_magic = "ToricExpFog";
	m_pTexture = pTexture;
	perApplicationVSConstantBuffer.density = fogDensity;
	perApplicationPSConstantBuffer.fogColor = fogColor;
	Initialize();
}
