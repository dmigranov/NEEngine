#pragma once
#include "Component.h"

class TransformComponent;

class UpdaterComponent :
    public Component
{
public:
    UpdaterComponent(std::function<void(double delta, Entity * pEntity)> func);
    void operator()(double delta, Entity* pEntity);
private:
    std::function<void(double delta, Entity* pEntity)> m_func;
};

