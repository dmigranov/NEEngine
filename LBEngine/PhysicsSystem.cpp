#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
#include "Entity.h"

PhysicsSystem::PhysicsSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::VelocityComponentType);

}

void PhysicsSystem::Execute(DWORD deltaTime)
{
	for (auto pEntity : m_entities)
	{
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
		VelocityComponent* velocity = (VelocityComponent*)pEntity->GetComponent(ComponentType::VelocityComponentType);


		
	}
}
