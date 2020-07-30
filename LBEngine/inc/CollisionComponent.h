#pragma once
#include "Component.h"
class CollisionComponent :
    public Component
{
public:
    CollisionComponent(double upleftX, double upleftY, double downrightX, double downrightY);
    CollisionComponent(DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright);

private:
    //AABB - axis-aligned bounding box
    DirectX::SimpleMath::Vector2 m_upleft, m_upright, m_downleft, m_downright;
};

