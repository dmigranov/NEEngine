#include "pch.h"
#include "ToricRenderSystem.h"

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
}

void ToricRenderSystem::Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext)
{
}
