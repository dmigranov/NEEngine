#include "pch.h"
#include "InputSystem.h"
#include "Entity.h"

#include "Game.h"

using namespace DirectX;

InputSystem::InputSystem() : System()
{
	SubscribeToComponentType<InputComponent>();

	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(Game::GetInstance().m_hwnd);

	//todo: RELATIVE AND ABSOLUTE
	m_mouse->SetMode(Mouse::MODE_RELATIVE);
	//m_mouse->SetMode(Mouse::MODE_ABSOLUTE);

}

void InputSystem::Execute(double deltaTime)
{
	pMouseState = m_mouse->GetState();
	pKeyboardState = m_keyboard->GetState();

	for (auto pEntity : m_entities)
	{
		InputComponent* inputComponent = pEntity->GetComponent<InputComponent>();
		inputComponent->SetInputData(pKeyboardState, pMouseState);
	}
}
