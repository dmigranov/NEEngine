#include "pch.h"
#include "InputComponent.h"


KeyboardState InputComponent::GetKeyboardState()
{
	return m_keyboardState;
}

MouseState InputComponent::GetMouseState()
{
	return m_mouseState;
}

void InputComponent::SetState(bool isRelative)
{
	if (m_mouse == nullptr)
		return;

}

void InputComponent::SetInputData(DirectX::Keyboard::State keyboardState, DirectX::Mouse::State mouseState)
{
	this->m_keyboardState = keyboardState;
	this->m_mouseState = mouseState;
}

void InputComponent::SetMouse(DirectX::Mouse* mouse)
{
	m_mouse = mouse;
}

InputComponent::InputComponent()
{}