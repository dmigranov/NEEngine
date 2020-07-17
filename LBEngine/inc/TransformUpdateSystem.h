#pragma once
#include "System.h"
class TransformUpdateSystem :
    public System
{
public:
    TransformUpdateSystem();
    virtual void Execute (double deltaTime) override;
};

