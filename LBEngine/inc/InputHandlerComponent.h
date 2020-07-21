#pragma once
#include "Component.h"

#include <functional>

class InputComponent;

class InputHandlerComponent :
    public Component
{
public:

    //todo: передавать ещё время?
    InputHandlerComponent(std::function<void(Entity *, DWORD, InputComponent&)> func);
    void operator()(Entity*, DWORD, InputComponent&);
private:
    std::function<void(Entity*, DWORD, InputComponent&)> m_inputHandlerFunc;
};

