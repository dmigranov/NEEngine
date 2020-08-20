#pragma once
#include "System.h"

class AABBCollisionComponent;
class CircleCollisionComponent;
class TransformComponent;
class ContactManifold;

class CollisionSystem :
    public System
{
public:
    CollisionSystem();
    virtual void Execute(double deltaTime) override;
private:
    virtual void AddEntity(Entity* pEntity) override;
    std::vector<Entity*> m_movableEntities;
    bool CheckCollision(Entity* pEntity1, Entity* pEntity2, ContactManifold& contactManifold );
    bool CheckDoubleAABBCollision(AABBCollisionComponent * pAABB1, AABBCollisionComponent* pAABB2, TransformComponent* pTransform1, TransformComponent* pTransform2);
    bool CheckDoubleCircleCollision(CircleCollisionComponent* pCircle1, CircleCollisionComponent* pCircle2, TransformComponent* pTransform1, TransformComponent* pTransform2);

};

