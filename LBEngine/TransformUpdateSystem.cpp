#include "pch.h"
#include "TransformUpdateSystem.h"
#include "Entity.h"
#include "TransformComponent.h"
#include "ComponentType.h"

TransformUpdateSystem::TransformUpdateSystem()
{
	SubscribeToComponentType(ComponentType::TransformComponentType);
}

void TransformUpdateSystem::Execute()
{
	for(auto pEntity : m_entities)
	{ 
		TransformComponent* transform = (TransformComponent*)pEntity->GetComponent(ComponentType::TransformComponentType);
		
		static int step = 0;
		step++;
		if (step > 5)
			step - 11;
		transform->Move(0, 0, step);
	}
}
