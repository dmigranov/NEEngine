#pragma once
#include "Component.h"

#include <functional>

class InputInfo;

class InputHandlerComponent :
    public Component
{
public:

    //todo: передавать ещё время?
    InputHandlerComponent(std::function<void(Entity *, DWORD, InputInfo&)> func);
    void operator()(Entity*, DWORD, InputInfo&);
private:
    std::function<void(Entity*, DWORD, InputInfo&)> m_inputHandlerFunc;
};

