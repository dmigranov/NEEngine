#include "pch.h"
#include "SphericalTransformComponent.h"

#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

double SphericalTransformComponent::m_radius = 0;

SphericalTransformComponent::SphericalTransformComponent() : SphericalTransformComponent(0, 0, 0)
{
	m_position = Vector4(0, 0, 0, 1);
}

SphericalTransformComponent::SphericalTransformComponent(double x, double y, double z)
{
	this->Move(x, y, z);
}

SphericalTransformComponent::SphericalTransformComponent(double x, double y, double z, double rx, double ry, double rz)
{
	this->Rotate(rx, ry, rz);
	this->Move(x, y, z);
}

SphericalTransformComponent::SphericalTransformComponent(DirectX::SimpleMath::Vector3 position) : SphericalTransformComponent(position.x, position.y, position.z)
{ }

SphericalTransformComponent::SphericalTransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation) : SphericalTransformComponent(position.x, position.y, position.z, rotation.x, rotation.y, rotation.z)
{ }

void SphericalTransformComponent::Move(DirectX::SimpleMath::Vector3 v)
{
	this->Move(v.x, v.y, v.z);
}

void SphericalTransformComponent::Move(double dx, double dy, double dz)
{
	//Matrix dT = SphericalRotationZW(dz) * SphericalRotationYW(dy) * SphericalRotationXW(dx);
	Matrix dT = SphericalRotationXW(dx) * SphericalRotationYW(dy) * SphericalRotationZW(dz);
	//T = R.Transpose() * dT * R * T;
	T = dT * T;

	m_shouldRecalcWorld = true;
	m_shouldRecalcView = true;
}

void SphericalTransformComponent::MoveAbsolute(double x, double y, double z, double w)
{
	//https://en.wikipedia.org/wiki/Rotations_in_4-dimensional_Euclidean_space

	Matrix T_temp;
	T_temp._11 = w;
	T_temp._12 = z;
	T_temp._13 = -y;
	T_temp._14 = x;

	T_temp._21 = -z;
	T_temp._22 = w;
	T_temp._23 = x;
	T_temp._24 = y;

	T_temp._31 = y;
	T_temp._32 = -x;
	T_temp._33 = w;
	T_temp._34 = z;

	T_temp._41 = -x;
	T_temp._42 = -y;
	T_temp._43 = -z;
	T_temp._44 = w;
	T = T_temp;

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

DirectX::SimpleMath::Vector4 SphericalTransformComponent::GetSphericalPosition()
{
	//if (m_shouldRecalcWorld)
		Recalculate();
	return m_position;
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

	m_position = m_radius * Vector4::Transform(Vector4(0, 0, 0, 1), m_world);

	m_shouldRecalcWorld = false;

	//std::cerr << "SphericalTransformComponent::Recalculate()" << std::endl;
}

void SphericalTransformComponent::RecalculateView()
{
	m_view = m_world.Transpose();
	m_shouldRecalcView = false;
	
	//std::cerr << "SphericalTransformComponent::RecalculateView()" << std::endl;
}

/*
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
*/

void SphericalTransformComponent::SetRadius(double radius)
{
	m_radius = radius;
	//matrices won't change if the radius is modified - therefore, we don't need to recalculate anything!
	//but the position will change!
}
