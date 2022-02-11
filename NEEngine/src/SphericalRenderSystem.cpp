#include "pch.h"
#include "SphericalRenderSystem.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "SphericalTransformComponent.h"

#include "SphericalEffect.h"

enum class SphericalVisibility {
	VISIBLE_NONE,
	VISIBLE_FRONT,
	VISIBLE_BACK,           //not really necessary but why not
	VISIBLE_ALL
};

SphericalRenderSystem::SphericalRenderSystem(double radius)
{
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<MeshComponent>();

	m_isDrawing = true;

	SetRadius(radius);
}

void SphericalRenderSystem::Execute(double deltaTime)
{
	auto& game = Game::GetInstance();
	ID3D11DeviceContext* pDeviceContext = game.GetDeviceContext();
	auto pDevice = game.GetDevice();

	//Input Assembler Stage - common
	//pDeviceContext->IASetInputLayout(game.g_d3dInputLayout);

	//Vertex Shader Stage
	//pDeviceContext->VSSetShader(game.g_d3dVertexShader, nullptr, 0);
	//pDeviceContext->VSSetConstantBuffers(0, 3, game.g_d3dVSConstantBuffers);

	//Geometry Shader Stage
	//pDeviceContext->GSSetShader(game.g_d3dGeometryShader, nullptr, 0);

	//Rasterizer Stage
	game.SetupRasterizer();

	//Pixel Shader Stage
	///pDeviceContext->PSSetShader(game.g_d3dPixelShader, nullptr, 0);
	//pDeviceContext->PSSetConstantBuffers(0, 1, &game.g_d3dPSConstantBuffer);
	//pDeviceContext->PSSetSamplers(0, 1, &game.g_d3dSamplerState);

	//Output Merger Stage (merges the output from the pixel shader onto the color and depth buffers)
	game.SetupOutputMerger();



	//TODO: more optimal per-effect traverse (и вынести может куда-то сам перебор в олтдельынй класс?)
	for (auto pEntity : m_entities)
	{
		if(pEntity->IsVisible())
			Render(pEntity, pDeviceContext, deltaTime);
	}
}

void SphericalRenderSystem::SetRadius(double radius)
{
	m_radius = radius;
	UpdateOnRadiusChange();
}

double SphericalRenderSystem::GetRadius()
{
	return m_radius;
}

void SphericalRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext, double deltaTime)
{
	SphericalTransformComponent* pTransformComponent = pEntity->GetComponent<SphericalTransformComponent>();
	MeshComponent* pMeshComponent = pEntity->GetComponent<MeshComponent>();
	auto topology = pMeshComponent->GetTopology();
	auto pEffect = pMeshComponent->GetEffect();

	if (!pEffect) //for debug: can be commented
	{
		std::cerr << "No effect found for the entity " << pEntity->GetName() << ", won't be rendered further!"  << std::endl;
		pEntity->SetVisible(false);
		return; 
	}
	
	//todo: добавить в SphericalEffect SetVisible с тремя градациями (ничего, instanceID = 0, всё)
	//и тут в зависмости от этого делать правильные вызовы отрисовки 

	/*
	if (auto * pSphEffect = dynamic_cast<SphericalEffect*>(pEffect)) {
		pSphEffect->SetRadius(m_radius);
	}
	else
	{
		std::cerr << "Effect supplied for the entity " << pEntity->GetName() << "does not support spherical rendering, won't be rendered further!" << std::endl;
		pEntity->SetVisible(false);
		return;
	}
	*/

	// Input Assembler Stage - unique for every mesh
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	unsigned int stride = pEffect->GetVertexBufferSize();
	unsigned int offset = 0;

	auto vertexBuffer = pMeshComponent->GetVertexBuffer();
	auto indexBuffer = pMeshComponent->GetIndexBuffer();
	pDeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	// Set the index buffer to active in the input assembler so it can be rendered.
	pDeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	pDeviceContext->IASetPrimitiveTopology(topology);

	pEffect->UpdatePerObject(pEntity, deltaTime);

	pDeviceContext->DrawIndexedInstanced(pMeshComponent->GetIndicesCount(), 2, 0, 0, 0);

	pEffect->Clean();
}

void SphericalRenderSystem::UpdateOnRadiusChange()
{
	SphericalTransformComponent::SetRadius(m_radius);
	SphericalEffect::SetRadius(m_radius);
	//TODO: set other classes' fields corresponding to the radius
}