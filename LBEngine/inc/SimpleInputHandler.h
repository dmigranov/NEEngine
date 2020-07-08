#pragma once
#include "InputHandler.h"
class SimpleInputHandler :
	public InputHandler
{
public:
	SimpleInputHandler(std::shared_ptr<Camera> camera, std::function<void(float deltaTime)> func, HWND window);
	void HandleInput(float deltaTime) override;
protected:
	void HandleKeyboard(float deltaTime);
	void HandleMouse(float deltaTime);
private:
	std::function<void(float deltaTime)> func;
};

