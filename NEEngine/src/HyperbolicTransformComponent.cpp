#include "pch.h"
#include "HyperbolicTransformComponent.h"

HyperbolicTransformComponent::HyperbolicTransformComponent() : HyperbolicTransformComponent(0, 0, 0)
{ }

HyperbolicTransformComponent::HyperbolicTransformComponent(double x, double y, double z)
{
	this->Move(x, y, z);
}

HyperbolicTransformComponent::HyperbolicTransformComponent(double x, double y, double z, double rx, double ry, double rz)
{
	this->Rotate(rx, ry, rz);
	this->Move(x, y, z);
}

HyperbolicTransformComponent::HyperbolicTransformComponent(DirectX::SimpleMath::Vector3 position) : HyperbolicTransformComponent(position.x, position.y, position.z)
{ }

HyperbolicTransformComponent::HyperbolicTransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation) : HyperbolicTransformComponent(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z)
{ }