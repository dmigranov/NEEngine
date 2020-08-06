#pragma once
#include "System.h"

#include <functional>

//https://gamedev.stackexchange.com/questions/56519/movement-physics-in-an-entity-component-system

class ActionSystem :
    public System
{
public:
    ActionSystem(const std::list<ComponentType>& types, std::function<void(Entity*, double)> func);
    virtual void Execute(double deltaTime) override;
private:
    std::function<void(Entity*, double&)> m_executeFunc;

};

//todo: изменить InputSystem
//InputInfo -> InputComponent. Задумка: 
//I would create an input componentand various other action components, like walk, jump, crawl, weapon, etc.The input component would have fields that describe how the entity wants to move, such as : walk left, jump, and attack.This can be supplied by the keyboard, by an AI, or over the network, which is implemented as a control component.
//The control systems - there is one for each control component type(keyboard, gamepad, network, AI, etc.); they set fields of the input component
//The action systems - there is one for each action component type(walk, jump, attack, interact, etc.); they look at the fields of the input componentand modify the physics state, weapon component, etc.
//Тогда у InputHandler не будет зависимости от ускорения, сил...
//Если надо для Jump - ок
//Можно даже эти action systems реализовать в виде лямбд
//наследоваться от ActionSystem, выбирать нужные компоненты и лямбдить экшн
