#include "pch.h"
#include "InputSystem.h"
#include "ComponentType.h"
#include "Entity.h"

#include "Game.h"

using namespace DirectX;

InputSystem::InputSystem()
{
	SubscribeToComponentType(ComponentType::InputComponentType);

	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(Game::GetInstance().m_hwnd);
	//m_mouse->SetMode(Mouse::MODE_RELATIVE);
}

void InputSystem::Execute(DWORD deltaTime)
{
	pMouseState = m_mouse->GetState();
	pKeyboardState = m_keyboard->GetState();

	for (auto pEntity : m_entities)
	{
		InputComponent* inputComponent = (InputComponent*)pEntity->GetComponent(ComponentType::InputComponentType);
		inputComponent->SetInputData(pKeyboardState, pMouseState);
	}
}
