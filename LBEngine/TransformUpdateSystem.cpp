#include "pch.h"
#include "TransformUpdateSystem.h"

#include "Entity.h"
#include "TransformComponent.h"

void TransformUpdateSystem::Update()
{
	for(auto pEntity : m_entities)
	{ 
		TransformComponent *transform = pEntity->GetComponent<TransformComponent>();
	}
}
