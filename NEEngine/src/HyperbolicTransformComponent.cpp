#include "pch.h"
#include "HyperbolicTransformComponent.h"

#include "HyperbolicMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

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

void HyperbolicTransformComponent::Move(DirectX::SimpleMath::Vector3 v)
{ 
	this->Move(v.x, v.y, v.z);
}

void HyperbolicTransformComponent::Move(double dx, double dy, double dz) //абсолютное движение!
{
	Matrix dT = HyperbolicTranslationZW(dz) * HyperbolicTranslationYW(dy) * HyperbolicTranslationXW(dx);
	T = dT * T;

	m_shouldRecalcWorld = true;
	m_shouldRecalcView = true;
}
