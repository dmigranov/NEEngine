#pragma once
#include "System.h"

#include <functional>


class ActionSystem :
    public System
{
public:
    ActionSystem(std::function<void(Entity*, DWORD)> func, ComponentType type, ...);
    virtual void Execute(DWORD deltaTime) override;
private:
    std::function<void(Entity*, DWORD&)> m_executeFunc;

};

