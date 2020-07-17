#include "pch.h"
#include "TransformUpdateSystem.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "ComponentType.h"

TransformUpdateSystem::TransformUpdateSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
}

void TransformUpdateSystem::Execute(DWORD deltaTime)
{
	for(auto pEntity : m_entities)
	{ 
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);

		transform->Move(0, 0.001, 0);
	}
}