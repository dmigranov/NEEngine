#include "pch.h"
#include "SphericalTransformComponent.h"

#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SphericalTransformComponent::SphericalTransformComponent() : SphericalTransformComponent(0, 0, 0)
{}

SphericalTransformComponent::SphericalTransformComponent(double x, double y, double z)
{
	this->Move(x, y, z);
}

SphericalTransformComponent::SphericalTransformComponent(double x, double y, double z, double rx, double ry, double rz)
{
	this->Rotate(rx, ry, rz);
	this->Move(x, y, z);
}

void SphericalTransformComponent::Move(DirectX::SimpleMath::Vector3 v)
{
	this->Move(v.x, v.y, v.z);
}

void SphericalTransformComponent::Move(double dx, double dy, double dz)
{
	Matrix dT = SphericalRotationZW(dz) * SphericalRotationYW(dy) * SphericalRotationXW(dx);
	//T = R.Transpose() * dT * R * T;
	T = dT * T;

	m_shouldRecalcWorld = true;
	m_shouldRecalcView = true;
}

void SphericalTransformComponent::Rotate(DirectX::SimpleMath::Vector3 r)
{
	this->Rotate(r.x, r.y, r.z);
}

void SphericalTransformComponent::Rotate(double deltaPitch, double deltaYaw, double deltaRoll) //x y z
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

void SphericalTransformComponent::SetPitchYawRoll(double pitch, double yaw, double roll)
{
	m_yaw = yaw;
	m_roll = roll;
	m_pitch = pitch;

	m_shouldRecalcWorld = true;
	m_shouldRecalcView = true;
}

void SphericalTransformComponent::Recalculate()
{
	RYaw = SphericalRotationXZ(-m_yaw);
	RPitch = SphericalRotationYZ(-m_pitch);
	RRoll = SphericalRotationXY(-m_roll);
	R = RPitch * RYaw * RRoll; //todo: order? 
	m_world = R * T;

	if (nullptr != m_pParent)
	{
		oldParentMatrix = m_pParent->GetWorld();
		m_world = m_world * oldParentMatrix;
	}

	m_position = Vector4::Transform(Vector4(0, 0, 0, 1), m_world);

	m_shouldRecalcWorld = false;

	std::cerr << "SphericalTransformComponent::Recalculate()" << std::endl;
}

void SphericalTransformComponent::RecalculateView()
{
	//todo: вызывется на каждом кадре - некомильфо
	m_view = m_world.Transpose();
	m_shouldRecalcView = false;
	
	//std::cerr << "SphericalTransformComponent::RecalculateView()" << std::endl;
}

void SphericalTransformComponent::SetWorld(const DirectX::SimpleMath::Matrix& world)
{
	//todo: проверить - правильно?

	auto realWorld = world;
	if (m_pParent != nullptr)
		realWorld = realWorld * m_pParent->GetWorld();
	m_world = realWorld;

	m_view = m_world.Transpose();

	m_shouldRecalcWorld = false;
	m_shouldRecalcView = false;
}