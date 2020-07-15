#pragma once
#include "Component.h"
class CameraComponent :
    public Component
{
public:
	CameraComponent();
	CameraComponent(double nearPlane, double farPlane, double fovY = 90.);
private:
	double m_fovY;
	double m_nearPlane;
	double m_farPlane;

	bool m_shouldRecalc;
};

