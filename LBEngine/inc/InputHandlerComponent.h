#pragma once
#include "Component.h"

#include <functional>

class InputInfo;

class InputHandlerComponent :
    public Component
{
public:

    //todo: передавать ещё время?
    InputHandlerComponent(std::function<void(Entity *, InputInfo&)> func);
    void operator()(Entity*, InputInfo&);
private:
    std::function<void(Entity*, InputInfo&)> m_inputHandlerFunc;
};

