#pragma once

typedef DirectX::Keyboard::State KeyboardState;

class InputInfo
{
public:
	KeyboardState GetKeyboardState();
private:
	friend class InputSystem;
	InputInfo(DirectX::Keyboard::State state);
	InputInfo();
    KeyboardState m_keyboardState;


};

