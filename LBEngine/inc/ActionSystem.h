#pragma once
#include "System.h"

#include <functional>

//https://gamedev.stackexchange.com/questions/56519/movement-physics-in-an-entity-component-system



template <class... T>
class ActionSystem :
    public System
{
public:
    ActionSystem(std::function<void(Entity*, double)> func)
    {
        //... после выражения - вызывает дял каждого элемента списка T...
        int dummy[] = { (SubscribeToComponentType<T>(), 0)... };

        m_executeFunc = func;
    }

    virtual void Execute(double deltaTime) override
    {
        for (auto pEntity : m_entities)
        {
            m_executeFunc(pEntity, deltaTime);
        }
    }
private:
    std::function<void(Entity*, double)> m_executeFunc;

};


