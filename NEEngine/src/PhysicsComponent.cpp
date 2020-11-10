#include "pch.h"
#include "PhysicsComponent.h"
#include "Force.h"
#include "Impulse.h"

using namespace DirectX::SimpleMath;

PhysicsComponent::PhysicsComponent(double mass)
{
	m_mass = mass;
}

void PhysicsComponent::AddForce(std::string forceName, Force force)
{
	m_forces.insert(std::pair<std::string, Force>(forceName, force));
}

Force PhysicsComponent::GetForce(std::string forceName)
{
	return m_forces[forceName];
}

void PhysicsComponent::RemoveForce(std::string forceName)
{
	m_forces.erase(forceName);
}

void PhysicsComponent::AddImpulse(std::string impulseName, Impulse force)
{
	m_impulses.insert(std::pair<std::string, Impulse>(impulseName, force));
}

Impulse PhysicsComponent::GetImpulse(std::string impulseName)
{
	return m_impulses[impulseName];
}

void PhysicsComponent::RemoveImpulse(std::string impulseName)
{
	m_impulses.erase(impulseName);
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

const DirectX::SimpleMath::Vector3& PhysicsComponent::GetAcceleration()
{
	return m_acceleration;
}

const double& PhysicsComponent::GetMass()
{
	return m_mass;
}
