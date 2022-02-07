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

void InputComponent::SetRelative(bool isRelative)
{
	if (m_mouse == nullptr)
		return;
	m_mouse->SetMode(isRelative ? DirectX::Mouse::MODE_RELATIVE : DirectX::Mouse::MODE_ABSOLUTE);
}

bool InputComponent::IsRelative()
{
	return m_mouseState.positionMode == DirectX::Mouse::MODE_RELATIVE;
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