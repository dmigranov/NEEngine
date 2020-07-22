#pragma once
#include "System.h"
class PhysicsSystem :
    public System
{
public:
    PhysicsSystem();
    virtual void Execute(DWORD deltaTime) override;
private:
    double m_gravity = 0.5;
};

