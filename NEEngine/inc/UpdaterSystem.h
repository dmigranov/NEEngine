#pragma once
#include "System.h"
class UpdaterSystem :
    public System
{
public:
    UpdaterSystem();
    virtual void Execute(double deltaTime) override;
};

