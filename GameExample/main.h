#pragma once

#include "Geometries/SphericalEllipticGeometry.h"

LRESULT CALLBACK WndProcFriedmann(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class FriedmannTimer {
public:
	FriedmannTimer(double initialSimulationTime, double frameTimeLimit, double muCoeff);
	void AddDelta(double deltaTime);
	bool IsTimeToRepaint();
	double GetSimulationTime();
	double GetMu();
	double GetFrameTime();
private:
	void SetFrameTime(double newTime);

	double m_currentSimulationTime;
	double m_currentFrameTime = 0.;
	double m_muCoeff = 1.;
	double m_frameTimeLimit;
};


HWND CreateFriedmannWindow();

void DrawFriedmann(HDC hdc);

void UpdateFriedmannWindow(double time);
void DrawFriedmannPoint(HDC hdc);

double RayTraceSpherePos(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, double r_projected_sq);
double RayTraceSphereNeg(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, double r_projected_sq);

FriedmannTimer* CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, SphericalTransformComponent * cameraTransform,
	System ** controlSystem, System ** radiusVisibilitySystem);

const int friedmann_w = 300, friedmann_h = 90;


