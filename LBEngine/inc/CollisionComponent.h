#pragma once
#include "Component.h"
class CollisionComponent :
    public Component
{
public:
    bool IsMovable();
protected:
    friend class CollisionSystem;

    std::function<void(Entity*, Entity*, double)> m_executeFunc;

    bool m_isMovable = false;
};

