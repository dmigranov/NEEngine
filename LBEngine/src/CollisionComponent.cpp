#include "pch.h"
#include "CollisionComponent.h"

using namespace DirectX::SimpleMath;

CollisionComponent::CollisionComponent(double upleftX, double upleftY, double downrightX, double downrightY) : CollisionComponent(Vector2(upleftX, upleftY), Vector2(downrightX, downrightY))
{}


CollisionComponent::CollisionComponent(DirectX::SimpleMath::Vector2 upleft, DirectX::SimpleMath::Vector2 downright)
{
	m_upleft = upleft;
	m_downright = downright;
}
