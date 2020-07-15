#include "pch.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent() :
	m_fovY(90.), m_shouldRecalc(true), m_nearPlane(0.01), m_farPlane(100.)
{}

CameraComponent::CameraComponent(double nearPlane, double farPlane, double fovY) :
	m_fovY(fovY), m_nearPlane(nearPlane), m_farPlane(farPlane), m_shouldRecalc(true)
{}

const DirectX::XMMATRIX& CameraComponent::GetProj()
{
	if (m_shouldRecalc)
		RecalculateProj();
	return m_proj;
}

void CameraComponent::RecalculateProj()
{
	//todo
}
