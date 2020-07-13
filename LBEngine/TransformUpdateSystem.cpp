#include "pch.h"
#include "TransformUpdateSystem.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "ComponentType.h"

void TransformUpdateSystem::Update()
{
	for(auto pEntity : m_entities)
	{ 
		TransformComponent *transform = (TransformComponent*)pEntity->GetComponent(TransformComponentType);
	}
}
