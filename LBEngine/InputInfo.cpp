#include "pch.h"
#include "InputInfo.h"

using namespace DirectX;

InputInfo::InputInfo()
{
	m_keyboard = std::make_unique<Keyboard>();
	m_mouse = std::make_unique<Mouse>();
}

bool InputInfo::IsKeyPressed(DirectX::Keyboard::Keys key)
{
	return m_keyboard->GetState().IsKeyDown(key);
}
