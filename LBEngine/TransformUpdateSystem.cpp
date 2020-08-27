#include "pch.h"
#include "TransformUpdateSystem.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "ComponentType.h"

TransformUpdateSystem::TransformUpdateSystem() : System()
{
	SubscribeToComponentType<TransformComponent>();
}

void TransformUpdateSystem::Execute(double deltaTime)
{
	for(auto pEntity : m_entities)
	{ 
		TransformComponent* transform = pEntity->GetComponent<TransformComponent>();

		transform->Move(0, 0.001, 0);
	}
}