#pragma once
#include "Component.h"

class UpdaterComponent :
    public Component
{
    //todo: продумать дизайн (может, просто передавать саму энтити?)
    //или только TransfComp?
public:
    UpdaterComponent(std::function<void(double delta)> func);
    void operator()(double delta);
private:
    std::function<void(double delta)> m_func;
};

