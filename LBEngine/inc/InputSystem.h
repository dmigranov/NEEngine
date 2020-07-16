#pragma once
#include "System.h"

class InputInfo;

class InputSystem :
    public System
{
public:
    InputSystem();
    virtual void Execute() override;


};

