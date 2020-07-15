#include "pch.h"
#include "CameraComponent.h"

using namespace DirectX::SimpleMath;

CameraComponent::CameraComponent() :
	m_fovY(90.), m_shouldRecalc(true), m_nearPlane(0.01), m_farPlane(100.), m_aspect(1.)
{}

CameraComponent::CameraComponent(double nearPlane, double farPlane, double aspect, double fovY) :
	m_fovY(fovY), m_nearPlane(nearPlane), m_farPlane(farPlane), m_shouldRecalc(true), m_aspect(aspect)
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
	m_aspect = width / height;
}

void CameraComponent::RecalculateProj()
{
	m_proj = Matrix::CreatePerspectiveFieldOfView(m_fovY, m_aspect, m_nearPlane, m_farPlane);
	m_shouldRecalc = false;
}
