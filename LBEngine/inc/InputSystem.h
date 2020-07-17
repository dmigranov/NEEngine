#pragma once
#include "System.h"
#include "InputInfo.h"

class InputSystem :
    public System
{
public:
    InputSystem();
    virtual void Execute() override;

    InputInfo m_inputInfo;
private:
    ;
};

