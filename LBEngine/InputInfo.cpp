#include "pch.h"
#include "InputInfo.h"


KeyboardState InputInfo::GetKeyboardState()
{
	return m_keyboardState;
}

MouseState InputInfo::GetMouseState()
{
	return m_mouseState;
}

InputInfo::InputInfo(DirectX::Keyboard::State keyboardState, DirectX::Mouse::State mouseState)
{
	this->m_keyboardState = keyboardState;
	this->m_mouseState = mouseState;
}

InputInfo::InputInfo()
{}