#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "Force.h"
#include "Impulse.h"

#include "CollisionComponent.h"

#include "Entity.h"

using namespace DirectX::SimpleMath;

PhysicsSystem::PhysicsSystem() : System()
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
		auto resultForce = Force::Zero;
		for(auto& forcePair : forces)
		{
			forcePair.second.Update();
			resultForce += forcePair.second;
		}

		auto& impulses = physics->m_impulses;
		auto resultImpulse = Impulse::Zero;
		for (auto& impulsePair : impulses)
		{
			resultImpulse += impulsePair.second;
		}
		impulses.clear();

		auto mass = physics->m_mass;
		if(mass > 0)
		{ 
			//сила - кг*м/с^2
			auto acceleration = resultForce.GetVector() / mass;
			physics->m_acceleration = acceleration;

			//todo: изменить интегрирование: не по эйлеру, как сейчас, а Verlet
			//импульс - кг*м/с, потому после деления на массу имеет размерность скорости
			auto velocity = physics->m_velocity + resultImpulse.GetVector() / mass + acceleration * deltaTime;

			physics->m_velocity = velocity;

			transform->Move(velocity * deltaTime);
		}
	}
}