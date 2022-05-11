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

void HyperbolicTransformComponent::Rotate(DirectX::SimpleMath::Vector3 r)
{
	this->Rotate(r.x, r.y, r.z);
}

void HyperbolicTransformComponent::Rotate(double deltaPitch, double deltaYaw, double deltaRoll)
{
	m_pitch += deltaPitch;
	m_yaw += deltaYaw;
	m_roll += deltaRoll;

	// keep longitude in sane range by wrapping
	if (m_yaw > DirectX::XM_PI)
		m_yaw -= DirectX::XM_2PI;
	else if (m_yaw < -DirectX::XM_PI)
		m_yaw += DirectX::XM_2PI;

	m_shouldRecalcWorld = true;
	m_shouldRecalcView = true;
}

void HyperbolicTransformComponent::SetPitchYawRoll(double pitch, double yaw, double roll)
{
	m_yaw = yaw;
	m_roll = roll;
	m_pitch = pitch;

	m_shouldRecalcWorld = true;
	m_shouldRecalcView = true;
}

DirectX::SimpleMath::Vector4 HyperbolicTransformComponent::GetHyperbolicPosition()
{
	Recalculate();
	return m_position;
}

void HyperbolicTransformComponent::Recalculate()
{
	RYaw = HyperbolicRotationXZ(-m_yaw);
	RPitch = HyperbolicRotationYZ(-m_pitch);
	RRoll = HyperbolicRotationXY(-m_roll);
	R = RPitch * RYaw * RRoll; //todo: order? 
	m_world = R * T;

	if (nullptr != m_pParent)
	{
		oldParentMatrix = m_pParent->GetWorld();
		m_world = m_world * oldParentMatrix;
	}

	m_position = Vector4::Transform(Vector4(0, 0, 0, 1), m_world);

	m_shouldRecalcWorld = false;

	//std::cerr << "HyperbolicTransformComponent::Recalculate()" << std::endl;
}

void HyperbolicTransformComponent::RecalculateView()
{
	m_view = m_world.Transpose();
	m_shouldRecalcView = false;

	//std::cerr << "HyperbolicTransformComponent::RecalculateView()" << std::endl;
}