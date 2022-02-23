#include "pch.h"
#include "SphericalDopplerEffect.h"
#include "Texture.h"
#include "Scene.h"

#include "SphericalMeshComponentFactory.h"	//to be able to import the struct

#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"
#include "DopplerComponent.h"
#include "Entity.h"

#include "Game.h"

#include "PixelShaderDoppler.h"
#include "SphDopplerVertexShader.h"
#include "EllDopplerVertexShader.h"

double SphericalDopplerEffect::m_radius_old = 1.;
bool SphericalDopplerEffect::m_isSimulationRunning = true;
bool SphericalDopplerEffect::m_isBackwards = false;


SphericalDopplerEffect::SphericalDopplerEffect(Texture* pTexture, Texture* pTextureAlt, double fogDensity, DirectX::XMVECTORF32 fogColor) : SphericalExpFogEffect(pTexture, fogDensity, fogColor)
{
	m_magic = "SphericalDoppler";
	perApplicationPSConstantBuffer.fogColor = fogColor;
	m_pTextureAlt = pTextureAlt;
	Initialize(); //parent Initialize already called
}

bool SphericalDopplerEffect::Initialize()
{
	//todo: ������������������� ��������� �������
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
	game.UpdateSubresource(g_d3dVSConstantBuffers[CB_Application], &perApplicationVSConstantBufferDoppler);

	constantBufferDesc.ByteWidth = sizeof(PerObjectPSConstantBuffer);
	SafeRelease(g_d3dPerObjectPSConstantBuffer);
	g_d3dPerObjectPSConstantBuffer = game.CreateBuffer(constantBufferDesc);
	game.UpdateSubresource(g_d3dPerObjectPSConstantBuffer, &perObjectPSConstantBuffer);

	return true;
}

void SphericalDopplerEffect::Deinitialize()
{
	SphericalExpFogEffect::Deinitialize();

	SafeRelease(g_d3dPerObjectPSConstantBuffer);
}

void SphericalDopplerEffect::UpdatePerObject(const Entity* pEntity, double deltaTime)
{
	if (m_radius_set)
	{
		if (m_radius != perApplicationVSConstantBufferDoppler.radius)
		{
			m_radius_old = perApplicationVSConstantBufferDoppler.radius; //���������� �� ��, ��� ������ ������������� ���������
			m_isSimulationRunning = true;
		}
		else
			m_isSimulationRunning = false;
		m_radius_set = false;
	}

	SphericalExpFogEffect::UpdatePerObject(pEntity, deltaTime);

	perApplicationVSConstantBufferDoppler.density = perApplicationVSConstantBuffer.density;
	perApplicationVSConstantBufferDoppler.projBack = perApplicationVSConstantBuffer.projBack;
	perApplicationVSConstantBufferDoppler.projFront = perApplicationVSConstantBuffer.projFront;
	if (m_isSimulationRunning)
	{
		perApplicationVSConstantBufferDoppler.radius = m_radius;
		perApplicationVSConstantBufferDoppler.radius_old = m_radius_old;
		if(!m_isBackwards)
			perApplicationVSConstantBufferDoppler.deltaTime = deltaTime;	
		else
			perApplicationVSConstantBufferDoppler.deltaTime = -deltaTime;

	}
			
	game.UpdateSubresource(g_d3dVSConstantBuffers[ConstantBuffer::CB_Application], &perApplicationVSConstantBufferDoppler);

	auto pDoppler = pEntity->GetComponent<DopplerComponent>();
	if (pDoppler != nullptr && pDoppler->IsSelected())
		perObjectPSConstantBuffer.isSelected = 1;
	else
		perObjectPSConstantBuffer.isSelected = 0;

	game.UpdateSubresource(g_d3dPerObjectPSConstantBuffer, &perObjectPSConstantBuffer);
	game.PSSetConstantBuffers(1, 1, &g_d3dPerObjectPSConstantBuffer);
	if (false)
	{
		if (m_pTextureAlt != nullptr)
		{     //Pixel Shader Stafe - unique for every stage
			auto shaderResource = m_pTextureAlt->GetTexture();
			game.PSSetShaderResources(1, &shaderResource);
		}
	}
}

void SphericalDopplerEffect::Clean()
{
	//not really neccessary but maybe set shaders to nullptr
}

void SphericalDopplerEffect::SetVelocityCoefficient(double velocity)
{
	perApplicationPSConstantBuffer.velocity_coeff = velocity;
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);
}

double SphericalDopplerEffect::GetVelocityCoefficient()
{
	return perApplicationPSConstantBuffer.velocity_coeff;
}

double SphericalDopplerEffect::GetOldRadius()
{
	return m_radius_old;
}

void SphericalDopplerEffect::SetBackwards(bool isBackwards)
{
	m_isBackwards = isBackwards;
}

void SphericalDopplerEffect::SetFogColor(DirectX::XMVECTORF32 fogColor)
{
	perApplicationPSConstantBuffer.fogColor = fogColor;
	game.UpdateSubresource(g_d3dPSConstantBuffer, &perApplicationPSConstantBuffer);
}