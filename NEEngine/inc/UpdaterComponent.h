#pragma once
#include "Component.h"
class UpdaterComponent :
    public Component
{
public:
    UpdaterComponent(std::function<void(float delta)> func);
private:
    std::function<void(float delta)> m_func;
};

