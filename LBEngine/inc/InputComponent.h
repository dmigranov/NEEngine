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
	InputComponent();
private:
	friend class InputSystem;
	void SetInputData(DirectX::Keyboard::State keyboardState, DirectX::Mouse::State mouseState);
    KeyboardState m_keyboardState;
	MouseState m_mouseState;


};

