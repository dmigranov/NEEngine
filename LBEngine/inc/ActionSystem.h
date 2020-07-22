#pragma once
#include "System.h"

#include <functional>


class ActionSystem :
    public System
{
public:
    ActionSystem(std::function<void(Entity*, DWORD)> func, const std::list<ComponentType> types);
    virtual void Execute(DWORD deltaTime) override;
private:
    std::function<void(Entity*, DWORD&)> m_executeFunc;

};

