#include "pch.h"
#include "InputSystem.h"
#include "InputHandlerComponent.h"
#include "ComponentType.h"
#include "Entity.h"
#include "InputInfo.h"

InputSystem::InputSystem()
{
}

void InputSystem::Execute()
{
	static InputInfo input;
	for (auto pEntity : m_entities)
	{
		InputHandlerComponent* inputHandler = (InputHandlerComponent*)pEntity->GetComponent(ComponentType::InputHandlerComponentType);

		(*inputHandler)(pEntity, input);
	}
}
