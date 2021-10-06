#pragma once
#include "Component.h"

class TransformComponent;

class UpdaterComponent :
    public Component
{
    //todo: ещё продумать дизайн (может, тоже на шаблонах сделать?)
public:
    UpdaterComponent(std::function<void(double delta, TransformComponent * pTransform)> func);
    void operator()(double delta, TransformComponent* pTransform);
private:
    std::function<void(double delta, TransformComponent* transform)> m_func;
};

