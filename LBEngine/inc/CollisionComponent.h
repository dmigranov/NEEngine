#pragma once
#include "Component.h"
class CollisionComponent :
    public Component
{
public:
    bool IsMovable();
    virtual CollisionComponentType GetType() = 0;
protected:
    friend class CollisionSystem;

    std::function<void(Entity*, Entity*, double)> m_executeFunc;

    bool m_isMovable = false;
};

