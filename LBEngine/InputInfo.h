#pragma once
class InputInfo
{
public:
	static void Update();
private:
	static DirectX::Keyboard  m_keyboard;
	static DirectX::Mouse     m_mouse;
};

