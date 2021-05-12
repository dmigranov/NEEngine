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
#include "PixelShader.h" 

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

bool ToricExpFogEffect::Initialize()
{
	//shaders
	//todo: vertex
	g_d3dPixelShader = game.CreatePixelShaderFromBytecode(g_ps, sizeof(g_ps));

	//input assembly:
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(EuclideanMeshComponentFactory::VertexData, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	//g_d3dInputLayout = game.CreateInputLayout(vertexLayoutDesc, _countof(vertexLayoutDesc), g_torexpvs, sizeof(g_sphexpvs));


	return false;
}
