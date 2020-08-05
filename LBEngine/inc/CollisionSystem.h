#pragma once
#include "System.h"
class CollisionSystem :
    public System
{
    CollisionSystem();
    virtual void Execute(DWORD deltaTime) override;
};

