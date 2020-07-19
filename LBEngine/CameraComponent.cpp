#include "pch.h"
#include "CameraComponent.h"

using namespace DirectX::SimpleMath;

CameraComponent::CameraComponent(bool isPerspective) :
	m_fovY(90.), m_shouldRecalc(true), m_nearPlane(0.001), m_farPlane(100.), m_aspect(1.), m_isPerspective(isPerspective)
{}

CameraComponent::CameraComponent(double nearPlane, double farPlane, double aspect, double fovY, bool isPerspective) :
	m_fovY(fovY), m_nearPlane(nearPlane), m_farPlane(farPlane), m_shouldRecalc(true), m_aspect(aspect), m_isPerspective(isPerspective)
{}

const DirectX::XMMATRIX& CameraComponent::GetProj()
{
	if (m_shouldRecalc)
		RecalculateProj();
	return m_proj;
}

void CameraComponent::SetFovY(double fovY)
{
	m_fovY = fovY;
	m_shouldRecalc = true;
}

void CameraComponent::SetAspect(double aspect)
{
	m_aspect = aspect;
	m_shouldRecalc = true;
}

void CameraComponent::SetOutputSize(double width, double height)
{
	m_width = width;
	m_height = height;
	m_aspect = width / height;
	m_shouldRecalc = true;
}

void CameraComponent::SetPerspective(bool isPerspective)
{
	m_isPerspective = isPerspective;
	m_shouldRecalc = true;
}

void CameraComponent::RecalculateProj()
{
	if (m_isPerspective)
		m_proj = DirectX::XMMatrixPerspectiveFovLH(m_fovY, m_aspect, m_nearPlane, m_farPlane);
	else
		m_proj = DirectX::XMMatrixOrthographicLH(m_aspect, 1, m_nearPlane, m_farPlane);
	m_shouldRecalc = false;
}
