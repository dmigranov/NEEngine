#include "pch.h"
#include "BitmapRenderSystem.h"
#include "BitmapComponent.h"
#include "Entity.h"
#include "TransformComponent.h"

BitmapRenderSystem::BitmapRenderSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
	SubscribeToComponentType(ComponentType::BitmapComponentType);
}

void BitmapRenderSystem::Execute(DWORD deltaTime)
{
	//todo: sort


	//сначала opaque (front to back)
	std::stable_sort(m_opaqueEntities.begin(), m_opaqueEntities.end(), [](Entity* e1, Entity* e2) -> bool {
		return e1->GetTransform()->GetPosition().z < e2->GetTransform()->GetPosition().z;
	});	//сортирует по возрастанию: сначала меньшие z...

	for (auto pEntity : m_opaqueEntities)
	{
		BitmapComponent* bitmapComponent = (BitmapComponent*)pEntity->GetComponent(ComponentType::BitmapComponentType);
	}
	//затем non opaque (back to front)

	for (auto pEntity : m_nonOpaqueEntities)
	{
		BitmapComponent* bitmapComponent = (BitmapComponent*)pEntity->GetComponent(ComponentType::BitmapComponentType);
	}
		
	//todo: в будущем переделать и избавиться от зависимостей от MeshComponent
	
}

void BitmapRenderSystem::AddEntity(Entity* pEntity)
{
	BitmapComponent* bitmapComponent = (BitmapComponent*)pEntity->GetComponent(ComponentType::BitmapComponentType);

	if (bitmapComponent->IsOpaque())
		m_opaqueEntities.push_back(pEntity);
	else
		m_nonOpaqueEntities.push_back(pEntity);

	m_entities.push_back(pEntity);

}
