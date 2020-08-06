#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Force.h"

#include "CollisionComponent.h"

#include "Entity.h"

using namespace DirectX::SimpleMath;

PhysicsSystem::PhysicsSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::PhysicsComponentType);
}

void PhysicsSystem::Execute(double deltaTime)
{
	for (auto pEntity : m_entities)
	{
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
		PhysicsComponent* physics = (PhysicsComponent*)pEntity->GetComponent(ComponentType::PhysicsComponentType);

		auto forces = physics->m_forces;

		auto resultForce = Force::Zero;
		for(auto pair : forces)
		{
			//todo: обновить силы
			resultForce += pair.second;
		}
		
		auto mass = physics->m_mass;
		if(mass > 0)
		{ 
			auto acceleration = resultForce.GetVector() / mass;
			physics->m_acceleration = acceleration;

			auto velocity = physics->m_velocity + acceleration * deltaTime;

			physics->m_velocity = velocity;

			transform->Move(velocity * deltaTime);

		}
	}
}
