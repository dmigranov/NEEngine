#pragma once
#include "Component.h"
class CollisionComponent :
    public Component
{
public:
    bool IsMovable();
private:
    friend class CollisionSystem;

    std::function<void(Entity*, Entity*, double)> m_executeFunc;

    bool m_isMovable = false;
};

