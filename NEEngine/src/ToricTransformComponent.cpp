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

void ToricTransformComponent::Normalize()
{
}
