#include "pch.h"
#include "CollisionSystem.h"
#include "CollisionComponent.h"
#include "Entity.h"


CollisionSystem::CollisionSystem()
{
	SubscribeToComponentType(ComponentType::CollisionComponentType);
	SubscribeToComponentType(ComponentType::TransformComponentType);

}

void CollisionSystem::Execute(DWORD deltaTime)
{
	//todo: оптимищировать: 
	//нет нужды проверять кирпичи на столкновения друг с другом. 
	//держать список движущихся объектов?
	//
	for (auto i = m_entities.begin(); i != m_entities.end(); ++i) {
		for (auto j = i; ++j != m_entities.end(); /**/) {
			auto pEntity1 = *i;
			auto pEntity2 = *j;

			CollisionComponent* pCollision1 = (CollisionComponent*)pEntity1->GetComponent(ComponentType::CollisionComponentType);
			CollisionComponent* pCollision2 = (CollisionComponent*)pEntity2->GetComponent(ComponentType::CollisionComponentType);

			TransformComponent* pTransform1 = (TransformComponent*)pEntity1->GetComponent(ComponentType::TransformComponentType);
			TransformComponent* pTransform2 = (TransformComponent*)pEntity2->GetComponent(ComponentType::TransformComponentType);

		}
	}
}
