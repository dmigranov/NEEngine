#include "pch.h"
#include "TransformUpdateSystem.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "ComponentType.h"

void TransformUpdateSystem::Execute()
{
	for(auto pEntity : m_entities)
	{ 
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
		transform->Move(0, 0, 1);
	}
}
