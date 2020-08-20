#pragma once
#include "CollisionComponent.h"
class CircleCollisionComponent :
    public CollisionComponent
{
public:
    CircleCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 centre, double radius);
    CircleCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 centre, double radius, bool isMovable);

    virtual CollisionComponentType GetType() override;

private:
    double m_radius;
    DirectX::SimpleMath::Vector2 m_centre;
};

