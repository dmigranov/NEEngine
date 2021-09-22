#include "pch.h"
#include "ToricTransformComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ToricTransformComponent::ToricTransformComponent() : TransformComponent()
{ }

ToricTransformComponent::ToricTransformComponent(double x, double y, double z) : TransformComponent(x, y, z)
{ }

ToricTransformComponent::ToricTransformComponent(DirectX::SimpleMath::Vector3 position) : TransformComponent(position)
{ }

ToricTransformComponent::ToricTransformComponent(double x, double y, double z, double rx, double ry, double rz, double sx, double sy, double sz) : TransformComponent(x, y, z, rx, ry, rz, sx, sy, sz)
{ }

ToricTransformComponent::ToricTransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale) : TransformComponent(position, rotation, scale)
{ }

/*
void ToricTransformComponent::Move(DirectX::SimpleMath::Vector3 v)
{
	TransformComponent::Move(v);
}

void ToricTransformComponent::Move(double x, double y, double z)
{
	this->Move(Vector3(x, y, z));
}
*/

void ToricTransformComponent::Recalculate()
{
	Normalize();
	TransformComponent::Recalculate();
}

void ToricTransformComponent::RecalculateView()
{
	Normalize();
	TransformComponent::RecalculateView();
}

void ToricTransformComponent::SetTorusDimensions(double tX, double tY, double tZ)
{
	torX = tX;
	torY = tY;
	torZ = tZ;
}

void ToricTransformComponent::Normalize()
{
	auto pos = pTransformComponent->GetPosition();

	float x = pos.x, y = pos.y, z = pos.z;
	double dx = 0, dy = 0, dz = 0;

	while (x > m_torX)
		dx -= m_torX;
	while (x < 0)
		dx += m_torX;

	while (y > m_torY)
		dy -= m_torY;
	while (y < 0)
		dy += m_torY;

	while (z > m_torZ)
		dz -= m_torZ;
	while (z < 0)
		dz += m_torZ;

	pTransformComponent->Move(dx, dy, dz);
}
