#pragma once
#include "System.h"
class CollisionSystem :
    public System
{
public:
    CollisionSystem();
    virtual void Execute(DWORD deltaTime) override;
private:

};

