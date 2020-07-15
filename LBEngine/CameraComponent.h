#pragma once
#include "Component.h"
class CameraComponent :
    public Component
{
public:
	CameraComponent();
	CameraComponent(double nearPlane, double farPlane, double aspect = 1., double fovY = 90.);
	const DirectX::XMMATRIX& GetProj();

	void SetFovY(double fovY);
	void SetAspect(double aspect);

private:
	void RecalculateProj();

	double m_fovY;
	double m_nearPlane;
	double m_farPlane;
	double m_aspect;

	bool m_shouldRecalc;
	DirectX::SimpleMath::Matrix m_proj;
};

