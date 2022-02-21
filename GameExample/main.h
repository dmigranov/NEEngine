#pragma once

#include "Geometries/SphericalEllipticGeometry.h"

LRESULT CALLBACK WndProcFriedmann(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND CreateFriedmannWindow();

void DrawFriedmann(HDC hdc);

void UpdateFriedmannWindow(double time);
void DrawFriedmannPoint(HDC hdc);

double RayTraceSpherePos(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, double r_projected_sq);
double RayTraceSphereNeg(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, double r_projected_sq);

void CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, System ** controlSystem, System ** radiusSystem, System ** visibilitySystem);

const int friedmann_w = 300, friedmann_h = 90;


class FriedmannTimer {
public:
	FriedmannTimer(double initialSimulationTime, double frameTimeLimit);
	void AddDelta(double deltaTime);
	//bool 
private:
	double m_currentSimulationTime;
	double m_currentFrameTime = 0.;
	double m_mu;
	double m_frameTimeLimit;
};
