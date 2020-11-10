#include "pch.h"
#include "CircleCollisionComponent.h"

#include "CollisionComponentType.h"

CircleCollisionComponent::CircleCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 centre, double radius)
{
	m_radius = radius;
	m_centre = centre;
	m_executeFunc = func;
}

CircleCollisionComponent::CircleCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 centre, double radius, bool isMovable) : CircleCollisionComponent(func, centre, radius)
{
	m_isMovable = isMovable;
}

CollisionComponentType CircleCollisionComponent::GetType()
{
	return CollisionComponentType::CircleCollisionComponentType;
}
