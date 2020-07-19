#include "pch.h"
#include "InputSystem.h"
#include "InputHandlerComponent.h"
#include "ComponentType.h"
#include "Entity.h"

#include "Game.h"

using namespace DirectX;

InputSystem::InputSystem()
{
	SubscribeToComponentType(ComponentType::InputHandlerComponentType);

	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(Game::GetInstance().m_hwnd);
	m_mouse->SetMode(Mouse::MODE_RELATIVE);
}

void InputSystem::Execute(DWORD deltaTime)
{
	auto ms = m_mouse->GetState();
	m_inputInfo = InputInfo(m_keyboard->GetState(), ms);

	for (auto pEntity : m_entities)
	{
		InputHandlerComponent* inputHandler = (InputHandlerComponent*)pEntity->GetComponent(ComponentType::InputHandlerComponentType);
		(*inputHandler)(pEntity, deltaTime, m_inputInfo);
	}
}
