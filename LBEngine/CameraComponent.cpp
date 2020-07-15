#include "pch.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent() :
	m_fovY(90.), m_shouldRecalc(true), m_nearPlane(0.01), m_farPlane(100.)
{}

CameraComponent::CameraComponent(double nearPlane, double farPlane, double fovY)
{
}
