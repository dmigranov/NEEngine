#include "pch.h"
#include "TransformComponent.h"

TransformComponent::TransformComponent() :
	m_pParent(NULL), m_position(0, 0, 0), m_shouldRecalc(true)
{}

TransformComponent::TransformComponent(double x, double y, double z) : 
	m_pParent(NULL), m_position(x, y, z), m_shouldRecalc(true)
{}

TransformComponent::TransformComponent(DirectX::SimpleMath::Vector3 position) :
	m_pParent(NULL), m_position(position), m_shouldRecalc(true)
{}

void TransformComponent::Recalculute()
{

	m_shouldRecalc = false;
}
