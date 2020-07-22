#pragma once
#include "System.h"

#include <functional>


class ActionSystem :
    public System
{
    ActionSystem(std::function<void(Entity*, DWORD)> func, ComponentType type, ...);
};

