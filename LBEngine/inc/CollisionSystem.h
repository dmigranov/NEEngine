#pragma once
#include "System.h"
class CollisionSystem :
    public System
{
public:
    CollisionSystem();
    virtual void Execute(double deltaTime) override;
private:
    virtual void AddEntity(Entity* pEntity) override;
    std::vector<Entity*> m_movableEntities;
    bool CheckCollision(Entity* pEntity1, Entity* pEntity2);
    bool CheckDoubleAABBCollision(Entity * pEntity1, Entity* pEntity2);
};

