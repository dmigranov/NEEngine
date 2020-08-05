#include "pch.h"
#include "PhysicsSystem.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"

#include "CollisionComponent.h"

#include "Entity.h"

using namespace DirectX::SimpleMath;

PhysicsSystem::PhysicsSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::PhysicsComponentType);

	//todo: перенести в отдельную систему и избавиться от зависимости
	//SubscribeToComponentType(ComponentType::CollisionComponentType);
}

void PhysicsSystem::Execute(DWORD deltaMillis)
{

	double deltaTime = deltaMillis / 1000.;
	for (auto pEntity : m_entities)
	{
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
		PhysicsComponent* physics = (PhysicsComponent*)pEntity->GetComponent(ComponentType::PhysicsComponentType);

		auto forces = physics->m_forces;

		auto resultForce = Vector3::Zero;
		for(auto pair : forces)
		{
			resultForce += pair.second;
		}
		
		auto mass = physics->m_mass;
		if(mass > 0)
		{ 
			auto acceleration = resultForce / mass;
			physics->m_acceleration = acceleration;

			auto velocity = physics->m_velocity + acceleration * deltaTime;
			physics->m_velocity = velocity;

			transform->Move(velocity * deltaTime);

		}
	}

	//todo Коллизии: можно перенести в CollisionSystem (тогда PhysicsSystem не будет зависеть от CollisionComponent)


	for (auto i = m_entities.begin(); i != m_entities.end(); ++i) {
		for (auto j = i; ++j != m_entities.end(); /**/) {
			auto pEntityFirst = *i;
			auto pEntitySecond = *j;

			std::cout << pEntityFirst << " " << pEntitySecond << std::endl;
		}
	}

}
