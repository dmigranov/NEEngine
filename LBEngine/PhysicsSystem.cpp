#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Entity.h"

PhysicsSystem::PhysicsSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::PhysicsComponentType);

}

void PhysicsSystem::Execute(DWORD deltaTime)
{
	for (auto pEntity : m_entities)
	{
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
		PhysicsComponent* physics = (PhysicsComponent*)pEntity->GetComponent(ComponentType::PhysicsComponentType);


		
	}
}
