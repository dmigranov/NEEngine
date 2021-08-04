#include "pch.h"
#include "HyperbolicRenderSystem.h"

#include "Entity.h"
#include "MeshComponent.h"
#include "HyperbolicTransformComponent.h"

#include "Effect.h"
HyperbolicRenderSystem::HyperbolicRenderSystem()
{
	SubscribeToComponentType<HyperbolicTransformComponent>();
	SubscribeToComponentType<MeshComponent>();

	m_isDrawing = true;
}

void HyperbolicRenderSystem::Execute(double deltaTime)
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

void HyperbolicRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
	
}
