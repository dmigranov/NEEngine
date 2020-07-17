#pragma once
#include "System.h"
#include "InputInfo.h"

class InputSystem :
    public System
{
public:
    InputSystem();
    virtual void Execute(double deltaTime) override;

    InputInfo m_inputInfo;
private:
    std::unique_ptr<DirectX::Keyboard>  m_keyboard;
    std::unique_ptr<DirectX::Mouse>     m_mouse;
};