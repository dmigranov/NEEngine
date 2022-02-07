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
	void SetRelative(bool isRelative);
	void IsRelative();
	InputComponent();
private:
	friend class InputSystem;
	void SetInputData(DirectX::Keyboard::State keyboardState, DirectX::Mouse::State mouseState);
	void SetMouse(DirectX::Mouse * mouse);
    KeyboardState m_keyboardState;
	MouseState m_mouseState;	
	DirectX::Mouse* m_mouse = nullptr;



};

