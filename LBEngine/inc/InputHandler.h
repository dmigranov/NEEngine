#pragma once
#include <Camera.h>
class InputHandler
{
public:
	virtual void HandleInput(float deltaTime) = 0;

protected:
	std::unique_ptr<DirectX::Keyboard>  m_keyboard;
	std::unique_ptr<DirectX::Mouse>     m_mouse;
	std::shared_ptr<Camera>             m_camera;
};

