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

TransformComponent::TransformComponent(double x, double y, double z, double rx, double ry, double rz, double sx, double sy, double sz) :
	m_pParent(NULL), m_position(x, y, z), m_rotation(rx, ry, rz), 
	m_scale(sx, sy, sz), m_shouldRecalc(true)
{}

TransformComponent::TransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale) :
	m_pParent(NULL), m_position(position), m_rotation(rotation), 
	m_scale(scale), m_shouldRecalc(true)
{}


void TransformComponent::Recalculute()
{
	//todo ...

	m_shouldRecalc = false;
}
