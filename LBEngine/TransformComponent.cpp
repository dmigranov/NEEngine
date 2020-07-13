#include "pch.h"
#include "TransformComponent.h"

using namespace DirectX::SimpleMath;

TransformComponent::TransformComponent() :
	m_pParent(NULL), m_positionLocal(0, 0, 0), m_shouldRecalc(true)
{}

TransformComponent::TransformComponent(double x, double y, double z) : 
	m_pParent(NULL), m_positionLocal(x, y, z), m_shouldRecalc(true)
{}

TransformComponent::TransformComponent(DirectX::SimpleMath::Vector3 position) :
	m_pParent(NULL), m_positionLocal(position), m_shouldRecalc(true)
{}

TransformComponent::TransformComponent(double x, double y, double z, double rx, double ry, double rz, double sx, double sy, double sz) :
	m_pParent(NULL), m_positionLocal(x, y, z), m_rotation(rx, ry, rz), 
	m_scale(sx, sy, sz), m_shouldRecalc(true)
{}

TransformComponent::TransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale) :
	m_pParent(NULL), m_positionLocal(position), m_rotation(rotation), 
	m_scale(scale), m_shouldRecalc(true)
{}


const Matrix& TransformComponent::GetWorld()
{
	if (m_shouldRecalc)
	{
		Recalculate();
	}

	return m_world;
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

	Vector4 up4 = m_matWorld * Vector4(0, 1, 0, 0);
	m_up = up4.ToVector3();
	m_up.Normalize();
	

	// ѕересчитываем матрицу View
	{
		m_matView = Matrix4x4::LookAtLH(m_positionLocal, m_positionLocal + m_forward, m_up);
	}

	m_shouldRecalc = false;
}
