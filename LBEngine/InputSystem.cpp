#include "pch.h"
#include "InputSystem.h"
#include "InputHandlerComponent.h"
#include "ComponentType.h"
#include "Entity.h"
#include "InputInfo.h"

void InputSystem::Execute()
{
	for (auto pEntity : m_entities)
	{
		InputHandlerComponent* inputHandler = (InputHandlerComponent*)pEntity->GetComponent(ComponentType::InputHandlerComponentType);

		(*inputHandler)(pEntity, InputInfo());
	}
}
