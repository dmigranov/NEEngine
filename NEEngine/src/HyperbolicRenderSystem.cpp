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
