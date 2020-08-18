#pragma once
#include "System.h"

class AABBCollisionComponent;
class TransformComponent;

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
    bool CheckDoubleAABBCollision(AABBCollisionComponent * pAABB1, AABBCollisionComponent* pAABB2, TransformComponent* pTransform1, TransformComponent* pTransform2);
};

