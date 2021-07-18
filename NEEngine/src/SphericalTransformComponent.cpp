#include "pch.h"
#include "SphericalTransformComponent.h"

#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//todo: реализовать

SphericalTransformComponent::SphericalTransformComponent()
{
}

void SphericalTransformComponent::Move(DirectX::SimpleMath::Vector3 v)
{
	//todo: multiply matrices...
	TransformComponent::Move(v); //todo: временно, для того чтобы все работало
}

void SphericalTransformComponent::Move(double x, double y, double z)
{
	this->Move(Vector3(x, y, z));
}

void SphericalTransformComponent::Rotate(DirectX::SimpleMath::Vector3 r)
{
	//todo
}

void SphericalTransformComponent::Rotate(double deltaYaw, double deltaPitch, double deltaRoll) //x y z
{
	m_pitch += deltaPitch;
	m_yaw += deltaYaw;
	m_roll += deltaRoll;

	// keep longitude in sane range by wrapping
	if (m_yaw > DirectX::XM_PI)
		m_yaw -= DirectX::XM_2PI;
	else if (m_yaw < -DirectX::XM_PI)
		m_yaw += DirectX::XM_2PI;

	RYaw = SphericalRotationXZ(-m_yaw);
	RPitch = SphericalRotationYZ(-m_pitch);

	R = RPitch * RYaw;
}

void SphericalTransformComponent::Recalculate()
{
	TransformComponent::Recalculate(); //todo: временно, для того чтобы все работало

	std::cerr << "SphericalTransformComponent::Recalculate()" << std::endl;
}

void SphericalTransformComponent::RecalculateView()
{
	//todo: вызывется на каждом кадре - некомильфо
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