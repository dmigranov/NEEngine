#include "pch.h"
#include "ToricRenderSystem.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "MeshComponent.h"


ToricRenderSystem::ToricRenderSystem(unsigned int replicationCount, double torX, double torY, double torZ)
{
	SubscribeToComponentType<TransformComponent>();
	SubscribeToComponentType<MeshComponent>();

	m_replicationCount = replicationCount;
	m_torX = torX;
	m_torY = torY;
	m_torZ = torZ;

	m_isDrawing = true;
}

void ToricRenderSystem::Execute(double deltaTime)
{
	auto& game = Game::GetInstance();
	ID3D11DeviceContext* pDeviceContext = game.GetDeviceContext();
	auto pDevice = game.GetDevice();

	//Rasterizer Stage
	game.SetupRasterizer();

	//Output Merger Stage (merges the output from the pixel shader onto the color and depth buffers)
	game.SetupOutputMerger();

	//todo: более оптимальный перебор по эффектам (и вынести может куда-то сам перебор в олтдельынй класс?)
	for (auto pEntity : m_entities)
	{
		if (pEntity->IsVisible())
			Render(pEntity, pDeviceContext);
	}
}

void ToricRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
}
