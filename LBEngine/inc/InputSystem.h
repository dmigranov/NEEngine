#pragma once
#include "System.h"
#include "InputComponent.h"

class InputSystem :
    public System
{
public:
    InputSystem();
    virtual void Execute(DWORD deltaTime) override;

    InputComponent m_inputInfo;
private:
    std::unique_ptr<DirectX::Keyboard>  m_keyboard;
    std::unique_ptr<DirectX::Mouse>     m_mouse;

    DirectX::Mouse::State pMouseState;
    DirectX::Keyboard::State pKeyboardState;

};