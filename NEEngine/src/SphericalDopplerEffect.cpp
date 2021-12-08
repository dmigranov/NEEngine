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

	constantBufferDesc.ByteWidth = sizeof(PerApplicationVSConstantBufferDoppler);
	SafeRelease(g_d3dVSConstantBuffers[CB_Application]);
	g_d3dVSConstantBuffers[CB_Application] = game.CreateBuffer(constantBufferDesc);
	game.UpdateSubresource(g_d3dVSConstantBuffers[CB_Application], &perApplicationVSConstantBuffer);

	return true;
}

void SphericalDopplerEffect::Deinitialize()
{
	SphericalExpFogEffect::Deinitialize();
}

void SphericalDopplerEffect::UpdatePerObject(const Entity* pEntity, double deltaTime)
{
	SphericalExpFogEffect::UpdatePerObject(pEntity, deltaTime);

	perApplicationVSConstantBufferDoppler.density = perApplicationVSConstantBuffer.density;
	perApplicationVSConstantBufferDoppler.projBack = perApplicationVSConstantBuffer.projBack;
	perApplicationVSConstantBufferDoppler.projFront = perApplicationVSConstantBuffer.projFront;
	perApplicationVSConstantBufferDoppler.deltaTime = deltaTime;
	perApplicationVSConstantBufferDoppler.radius = m_radius;
	perApplicationVSConstantBufferDoppler.radius_old = m_radius_old;
	//m_radius_old = m_radius;
			
	game.UpdateSubresource(g_d3dVSConstantBuffers[ConstantBuffer::CB_Application], &perApplicationVSConstantBufferDoppler);

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
	m_radius_old = m_radius;
	m_radius = radius;
}

void SphericalDopplerEffect::SetFogColor(DirectX::XMVECTORF32 fogColor)
{
	perApplicationPSConstantBuffer.fogColor = fogColor;
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);
}
