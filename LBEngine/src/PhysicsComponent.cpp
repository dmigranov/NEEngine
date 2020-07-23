#include "pch.h"
#include "PhysicsComponent.h"

using namespace DirectX::SimpleMath;

PhysicsComponent::PhysicsComponent()
{
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
