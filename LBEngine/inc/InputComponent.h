#pragma once

#include "Component.h"

typedef DirectX::Keyboard::State KeyboardState;
typedef DirectX::Mouse::State MouseState;

class InputComponent :
	public Component
{
public:
	KeyboardState GetKeyboardState();
	MouseState GetMouseState();
private:
	friend class InputSystem;
	InputComponent(DirectX::Keyboard::State keyboardState, DirectX::Mouse::State mouseState);
	InputComponent();
    KeyboardState m_keyboardState;
	MouseState m_mouseState;


};

