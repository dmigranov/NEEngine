#include "pch.h"
#include "TransformComponent.h"

using namespace DirectX::SimpleMath;

TransformComponent::TransformComponent() :
	m_pParent(NULL), m_positionLocal(0, 0, 0), m_shouldRecalcWorld(true), m_shouldRecalcView(true), m_scale(1, 1, 1)
{}

TransformComponent::TransformComponent(double x, double y, double z) : 
	m_pParent(NULL), m_positionLocal(x, y, z), m_shouldRecalcWorld(true), m_shouldRecalcView(true), m_scale(1, 1, 1)
{}

TransformComponent::TransformComponent(DirectX::SimpleMath::Vector3 position) :
	m_pParent(NULL), m_positionLocal(position), m_shouldRecalcWorld(true), m_shouldRecalcView(true), m_scale(1, 1, 1)
{}

TransformComponent::TransformComponent(double x, double y, double z, double rx, double ry, double rz, double sx, double sy, double sz) :
	m_pParent(NULL), m_positionLocal(x, y, z), m_rotation(rx, ry, rz), 
	m_scale(sx, sy, sz), m_shouldRecalcWorld(true), m_shouldRecalcView(true)
{}

TransformComponent::TransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale) :
	m_pParent(NULL), m_positionLocal(position), m_rotation(rotation), 
	m_scale(scale), m_shouldRecalcWorld(true), m_shouldRecalcView(true)
{}

void TransformComponent::Move(Vector3 v)
{
	m_positionLocal += v;
	m_shouldRecalcWorld = true;
	m_shouldRecalcView = true;
}

void TransformComponent::Move(double x, double y, double z)
{
	this->Move(Vector3(x, y, z));
}

const DirectX::SimpleMath::Matrix& TransformComponent::GetWorld()
{
	if (m_shouldRecalcWorld)
	{
		Recalculate();
	}

	return m_world;
}

const DirectX::SimpleMath::Matrix& TransformComponent::GetView()
{
	if (m_shouldRecalcWorld)
		Recalculate();
	if (m_shouldRecalcView)
		RecalculateView();
	return m_view;
}

void TransformComponent::Recalculate()
{
	Matrix matTransLocal = Matrix::CreateTranslation(m_positionLocal);
	Matrix matRotLocal = Matrix::CreateRotationX(m_rotation.x) * Matrix::CreateRotationY(m_rotation.y) * Matrix::CreateRotationZ(m_rotation.z);
	Matrix matScale = Matrix::CreateScale(m_scale);

	m_world = matScale * matRotLocal * matTransLocal;

	if (nullptr != m_pParent)
	{
		Matrix matWorldParent = m_pParent->GetWorld();
		m_world = m_world * matWorldParent;
	}

	Vector4 position4 = Vector4::Transform(Vector4(0, 0, 0, 1), m_world);
	m_position = Vector3(position4.x, position4.y, position4.z);	//global position
	
	
	Vector4 forward4 = Vector4::Transform(Vector4(0, 0, 1, 0), m_world);
	m_forward = Vector3(forward4.x, forward4.y, forward4.z);
	m_forward.Normalize();

	Vector4 right4 = Vector4::Transform(Vector4(1, 0, 0, 0), m_world);
	m_right = Vector3(right4.x, right4.y, right4.z);
	m_right.Normalize();

	Vector4 up4 = Vector4::Transform(Vector4(0, 1, 0, 0), m_world);
	m_up = Vector3(up4.x, up4.y, up4.z);
	m_up.Normalize();
	
	m_shouldRecalcWorld = false;
}

void TransformComponent::RecalculateView()
{
	m_view = Matrix::CreateLookAt(m_position, m_position + m_forward, m_up);

	m_shouldRecalcView = false;
}
