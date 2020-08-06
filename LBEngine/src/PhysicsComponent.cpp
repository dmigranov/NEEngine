#include "pch.h"
#include "PhysicsComponent.h"
#include "..\inc\PhysicsComponent.h"

using namespace DirectX::SimpleMath;

PhysicsComponent::PhysicsComponent(double mass)
{
	m_mass = mass;
}

void PhysicsComponent::AddForce(std::string forceName, DirectX::SimpleMath::Vector3 force)
{
	m_forces.insert(std::pair<std::string, Vector3>(forceName, force));
}

DirectX::SimpleMath::Vector3 PhysicsComponent::GetForce(std::string forceName)
{
	return m_forces[forceName];
}

void PhysicsComponent::RemoveForce(std::string forceName)
{
	m_forces.erase(forceName);
}

void PhysicsComponent::SetAcceleration(Vector3 a)
{
	m_acceleration = a;
}

void PhysicsComponent::SetVelocity(DirectX::SimpleMath::Vector3 v)
{
	m_velocity = v;
}

const DirectX::SimpleMath::Vector3& PhysicsComponent::GetVelocity()
{
	return m_velocity;
}

const double& PhysicsComponent::GetMass()
{
	return m_mass;
}
