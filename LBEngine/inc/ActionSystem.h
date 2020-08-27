#pragma once
#include "System.h"

#include <functional>

//https://gamedev.stackexchange.com/questions/56519/movement-physics-in-an-entity-component-system

class ActionSystem :
    public System
{
public:
    //todo:
    //ActionSystem(const std::list<ComponentType>& types, std::function<void(Entity*, double)> func);
    virtual void Execute(double deltaTime) override;
private:
    std::function<void(Entity*, double)> m_executeFunc;

};
