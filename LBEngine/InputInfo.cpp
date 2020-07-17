#include "pch.h"
#include "InputInfo.h"


InputInfo::InputInfo()
{
}

bool InputInfo::IsKeyPressed(DirectX::Keyboard::Keys key)
{
	return m_keyboard->GetState().IsKeyDown(key);
}
