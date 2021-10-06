#pragma once
#include "Component.h"

class TransformComponent;

class UpdaterComponent :
    public Component
{
    //todo: продумать дизайн (может, просто передавать саму энтити?)
    //или только TransfComp?
public:
    UpdaterComponent(std::function<void(double delta, TransformComponent * transform)> func);
    void operator()(double delta, TransformComponent* transform);
private:
    std::function<void(double delta, TransformComponent* transform)> m_func;
};

