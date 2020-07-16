#include "pch.h"
#include "InputInfo.h"


DirectX::Keyboard::State& InputInfo::GetKeys()
{
	auto k = m_keyboard.GetState();
	return k;
}
