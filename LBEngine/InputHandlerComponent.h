#pragma once
#include "Component.h"

#include <functional>

class InputInfo;

class InputHandlerComponent :
    public Component
{
public:

    //todo: чем-то похож на апдейтер и InputHandler: сделать также
    //через лямбды.
    //также сделать InputSystem, апдейтер которой вызывает лямбду...
    InputHandlerComponent(std::function<void(Entity *, InputInfo)> func);
    void operator()(Entity*, InputInfo);
private:
    std::function<void(Entity*, InputInfo)> m_inputHandlerFunc;
};

