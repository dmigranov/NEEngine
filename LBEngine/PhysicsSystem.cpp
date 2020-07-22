#include "pch.h"
#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::VelocityComponentType);

}

void PhysicsSystem::Execute(DWORD deltaTime)
{
}
