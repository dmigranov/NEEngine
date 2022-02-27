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

class SelectionSystem :
	public System
{
public:
	SelectionSystem(InputComponent* pInputComponent, double initialObjectRadius);
	virtual void Execute(double deltaTime) override;
private:
	InputComponent* m_pInputComponent;
	Game& m_game;
	SphericalTransformComponent* m_pCameraTransform;
	SphericalCameraComponent* m_pCameraComponent;

	double m_initialObjectRadius;
};

class RadiusUpdateSystem : public System {
public:
	RadiusUpdateSystem(FriedmannTimer * timer, SphericalRenderSystem * renderSystem);
	virtual void Execute(double deltaTime) override;
private:
	FriedmannTimer* m_timer;
	SphericalRenderSystem* m_renderSystem;
};


HWND CreateFriedmannWindow();

void DrawFriedmann(HDC hdc);

void UpdateFriedmannWindow(double time);
void DrawFriedmannPoint(HDC hdc);

double RayTraceSpherePos(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, double r_projected_sq);
double RayTraceSphereNeg(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, double r_projected_sq);
double RayTraceSphereMouse(double mouseX, double mouseY, SphericalTransformComponent* pSphericalTransform, 
	DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, double r_sphere, double w_sphere);



FriedmannTimer* CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, SphericalTransformComponent * cameraTransform, SphericalRenderSystem* renderSystem, InputComponent * inputComponent,
	System ** controlSystem, System ** visibilitySystem, System ** radiusUpdateSystem, System ** animationSystem, SelectionSystem ** selectionSystem);

const int friedmann_w = 300, friedmann_h = 90;


