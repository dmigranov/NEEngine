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

SphericalDopplerEffect::SphericalDopplerEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor) : SphericalExpFogEffect(pTexture, fogDensity, fogColor)
{
	m_magic = "SphericalDoppler";
	perApplicationPSConstantBuffer.fogColor = fogColor;
	Initialize(); //parent Initialize already called
}

bool SphericalDopplerEffect::Initialize()
{
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
	//game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer); //todo: перенести
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
	double old_radius = m_radius;
	m_radius = radius;
	perApplicationVSConstantBuffer.radius = m_radius;
	if (old_radius != m_radius)
	{
		//todo: с увеличением радиуса в k раз расстояние увеличится в k раз (вне зависимости от координат объекта
		//new_dist = new_radius/old_radius * old_dist
		//new_dist - old_dist = (new_radius/old_radius - 1) * old_dist
	}

}

void SphericalDopplerEffect::SetFogColor(DirectX::XMVECTORF32 fogColor)
{
	perApplicationPSConstantBuffer.fogColor = fogColor;
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);
}
