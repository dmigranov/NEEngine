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

	return true;
}

void SphericalDopplerEffect::Deinitialize()
{
	SphericalExpFogEffect::Deinitialize();
}

void SphericalDopplerEffect::UpdatePerObject(const Entity* pEntity)
{
	SphericalExpFogEffect::UpdatePerObject(pEntity);
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer); //todo: перенести
}

void SphericalDopplerEffect::Clean()
{
	//not really neccessary but maybe set shaders to nullptr
}

void SphericalDopplerEffect::ChangeVelocity(double velocity)
{
	perApplicationPSConstantBuffer.velocity = velocity;
}

void SphericalDopplerEffect::SetRadius(double radius)
{
	SphericalExpFogEffect::SetRadius(radius);

}
