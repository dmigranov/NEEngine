#include "pch.h"
#include "AABBCollisionComponent.h"
#include "CollisionComponentType.h"

using namespace DirectX::SimpleMath;

AABBCollisionComponent::AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY) : AABBCollisionComponent(func, Vector2(upleftX, upleftY), Vector2(downrightX, downrightY))
{}

AABBCollisionComponent::AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, double upleftX, double upleftY, double downrightX, double downrightY, bool isMovable) : AABBCollisionComponent(func, upleftX, upleftY, downrightX, downrightY)
{
	m_isMovable = isMovable;
}

AABBCollisionComponent::AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright)
{
	m_upleft = upleft;
	m_downright = downright;
	m_executeFunc = func;
}

AABBCollisionComponent::AABBCollisionComponent(std::function<void(Entity*, Entity*, double)> func, DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright, bool isMovable) : AABBCollisionComponent(func, upleft, downright)
{
	m_isMovable = isMovable;
}

CollisionComponentType AABBCollisionComponent::GetType()
{
	return CollisionComponentType::AAABCollisionComponentType;
}
