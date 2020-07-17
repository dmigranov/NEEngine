#include "pch.h"
#include "InputSystem.h"
#include "InputHandlerComponent.h"
#include "ComponentType.h"
#include "Entity.h"

using namespace DirectX;

InputSystem::InputSystem() 
{
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
}

void InputSystem::Execute()
{
	m_inputInfo = InputInfo(m_keyboard->GetState());
	for (auto pEntity : m_entities)
	{
		InputHandlerComponent* inputHandler = (InputHandlerComponent*)pEntity->GetComponent(ComponentType::InputHandlerComponentType);
		(*inputHandler)(pEntity, m_inputInfo);
	}
}
