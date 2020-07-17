#include "pch.h"
#include "InputSystem.h"
#include "InputHandlerComponent.h"
#include "ComponentType.h"
#include "Entity.h"

InputSystem::InputSystem()
{
}

void InputSystem::Execute()
{
	for (auto pEntity : m_entities)
	{
		InputHandlerComponent* inputHandler = (InputHandlerComponent*)pEntity->GetComponent(ComponentType::InputHandlerComponentType);

		(*inputHandler)(pEntity, m_inputInfo);
	}
}
