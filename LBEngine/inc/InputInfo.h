#pragma once

typedef DirectX::Keyboard::State KeyboardState;
typedef DirectX::Mouse::State MouseState;

class InputInfo
{
public:
	KeyboardState GetKeyboardState();
	MouseState GetMouseState();
private:
	friend class InputSystem;
	InputInfo(DirectX::Keyboard::State keyboardState, DirectX::Mouse::State mouseState);
	InputInfo();
    KeyboardState m_keyboardState;
	MouseState m_mouseState;


};

