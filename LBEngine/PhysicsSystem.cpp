#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Force.h"
#include "Impulse.h"

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

		auto& forces = physics->m_forces;
		auto& impulses = physics->m_impulses;

		auto resultForce = Force::Zero;
		auto resultImpulse = Impulse::Zero;

		for(auto& forcePair : forces)
		{
			forcePair.second.Update();
			resultForce += forcePair.second;
		}
		for (auto& impulsePair : impulses)
		{
			resultImpulse += impulsePair.second;
		}
//импульс - m*v2 - m*v1...
		auto mass = physics->m_mass;
		if(mass > 0)
		{ 
			auto acceleration = resultForce.GetVector() / mass;
			physics->m_acceleration = acceleration;

			auto velocity = physics->m_velocity + acceleration * deltaTime;

			physics->m_velocity = velocity;
			//std::cout << velocity.x << std::endl;

			transform->Move(velocity * deltaTime);

		}
		impulses.clear();
		int t = 5;
	}
}
