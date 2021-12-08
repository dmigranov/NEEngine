#include "pch.h"
#include "SphericalDopplerEffect.h"
#include "Texture.h"
#include "Scene.h"

#include "SphericalMeshComponentFactory.h"	//to be able to import the struct

#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"
#include "Entity.h"

#include "Game.h"

#include "PixelShaderDoppler.h"
#include "SphDopplerVertexShader.h"
#include "EllDopplerVertexShader.h"


SphericalDopplerEffect::SphericalDopplerEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor) : SphericalExpFogEffect(pTexture, fogDensity, fogColor)
{
	m_magic = "SphericalDoppler";
	perApplicationPSConstantBuffer.fogColor = fogColor;
	Initialize(); //parent Initialize already called
}

bool SphericalDopplerEffect::Initialize()
{
	//todo: проинициализировать вершинные шейдеры
	SafeRelease(g_d3dVertexShaderSph);
	g_d3dVertexShaderSph = game.CreateVertexShaderFromBytecode(g_sph_dop, sizeof(g_sph_dop));

	SafeRelease(g_d3dVertexShaderEll);
	g_d3dVertexShaderEll = game.CreateVertexShaderFromBytecode(g_ell_dop, sizeof(g_ell_dop));

	SafeRelease(g_d3dPixelShader);
	g_d3dPixelShader = game.CreatePixelShaderFromBytecode(g_psd, sizeof(g_psd));


	D3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(PerApplicationPSConstantBufferDoppler);
	SafeRelease(g_d3dPSConstantBuffer);
	g_d3dPSConstantBuffer = game.CreateBuffer(constantBufferDesc);
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);

	return true;
}

void SphericalDopplerEffect::Deinitialize()
{
	SphericalExpFogEffect::Deinitialize();
}

void SphericalDopplerEffect::UpdatePerObject(const Entity* pEntity, double deltaTime)
{
	SphericalExpFogEffect::UpdatePerObject(pEntity, deltaTime);
			
	//todo: с увеличением радиуса в k раз расстояние увеличится в k раз (вне зависимости от координат объекта
	//new_dist = new_radius/old_radius * old_dist
	//new_dist - old_dist = (new_radius/old_radius - 1) * old_dist
	//это можно сделать в шейдере!
	//и если мы примем старый радиус за 1, то формула примет вид 
	//new_dist - old_dist = (new_radius - 1) * old_dist, где old_dist - расстояние в пространстве с радиусом 1!
	//но нужен другой вертексный шейдер (пара: для сф. и элл пространств)
	//new_dist - old_dist = (new_radius - 1) * new_dist / new_radius = new_dist * (1 - 1/new_radius)
}

void SphericalDopplerEffect::Clean()
{
	//not really neccessary but maybe set shaders to nullptr
}

void SphericalDopplerEffect::SetVelocity(double velocity)
{
	perApplicationPSConstantBuffer.velocity = velocity;
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);
}

double SphericalDopplerEffect::GetVelocity()
{
	return perApplicationPSConstantBuffer.velocity;
}

void SphericalDopplerEffect::SetRadius(double radius)
{
	m_old_radius = m_radius;
	m_radius = radius;
	perApplicationVSConstantBuffer.radius = m_radius;
}

void SphericalDopplerEffect::SetFogColor(DirectX::XMVECTORF32 fogColor)
{
	perApplicationPSConstantBuffer.fogColor = fogColor;
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);
}
