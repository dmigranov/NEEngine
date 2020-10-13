#pragma once
#include "System.h"

#include <functional>

//https://gamedev.stackexchange.com/questions/56519/movement-physics-in-an-entity-component-system

//Args&& is rvalue reference
//legal: T&& r = T();
template<typename... Args> inline void pass(Args&&...) {}

template<typename... Args> inline void expand(Args&&... args)
{
    pass(SubscribeToComponentType(args)...);
}

template <class... Types>
class ActionSystem :
    public System
{
public:
    //todo:
    //ActionSystem(const std::list<ComponentType>& types, std::function<void(Entity*, double)> func);
    ActionSystem(std::function<void(Entity*, double)>)
    {
        //for (auto type : types)
        //    SubscribeToComponentType(type);



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


