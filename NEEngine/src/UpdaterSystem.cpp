#include "pch.h"
#include "UpdaterSystem.h"

#include "Entity.h"
#include "UpdaterComponent.h"

UpdaterSystem::UpdaterSystem() : System()
{
	SubscribeToComponentType<TransformComponent>();
	SubscribeToComponentType<UpdaterComponent>();
}

void UpdaterSystem::Execute(double deltaTime)
{
	for (auto pEntity : m_entities)
	{
		UpdaterComponent* pUpdater = pEntity->GetComponent<UpdaterComponent>();
		TransformComponent* pTransform = pEntity->GetComponent<TransformComponent>();
		(*pUpdater)(deltaTime, pTransform);
	}
}
