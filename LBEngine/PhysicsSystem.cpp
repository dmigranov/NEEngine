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


		//todo:надо по ссылке и форсес и импулсес тк изменения не синкуются
		auto forces = physics->m_forces;
		auto impulses = physics->m_impulses;
		auto resultForce = Force::Zero;
		for(auto pair : forces)
		{
			pair.second.Update();
			resultForce += pair.second;
		}
		
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
		impulses.clear();	//неправильно, так как никак не влияет на настоящий impulses, это его клон
		int t = 5;
	}
}
