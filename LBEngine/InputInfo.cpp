#include "pch.h"
#include "InputInfo.h"


KeyboardState InputInfo::GetKeyboardState()
{
	return m_keyboardState;
}

InputInfo::InputInfo(DirectX::Keyboard::State state)
{
	this->m_keyboardState = state;
}

InputInfo::InputInfo()
{}