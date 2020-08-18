#pragma once
#include "CollisionComponent.h"

//AABB - axis-aligned bounding box

class AABBCollisionComponent :
    public CollisionComponent
{
public:
    AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY);
    AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY, bool isMovable);
    AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright);
    AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright, bool isMovable);

    virtual CollisionComponentType GetType() override;



private:
    DirectX::SimpleMath::Vector2 m_upleft, m_downright; //m_upright, m_downleft, - избыточно

};

