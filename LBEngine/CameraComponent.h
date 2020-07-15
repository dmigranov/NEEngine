#pragma once
#include "Component.h"
class CameraComponent :
    public Component
{
public:
	CameraComponent();
	CameraComponent(double nearPlane, double farPlane, double fovY = 90.);
	const DirectX::XMMATRIX& GetProj();

private:
	void RecalculateProj();

	double m_fovY;
	double m_nearPlane;
	double m_farPlane;

	bool m_shouldRecalc;
	DirectX::SimpleMath::Matrix m_proj;
};

