#pragma once

#include "Geometries/SphericalEllipticGeometry.h"
#include "DopplerComponent.h"

LRESULT CALLBACK WndProcFriedmann(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

class FriedmannTimer {
public:
	FriedmannTimer(double initialSimulationTime, double frameUpdateTimeLimit, double muCoeff);
	void AddDelta(double deltaTime);
	bool IsTimeToRepaint();
	double GetSimulationTime();
	double GetEta();
	double GetFrameTime();

	void SetMuCoeff(double muCoeff); //coeff is speed
	double GetMuCoeff();
private:
	void SetFrameTime(double newTime);

	double m_currentSimulationTime;
	double m_currentFrameTime = 0.;
	double m_mu = 0;

	double m_muCoeff = 1.;
	double m_frameUpdateTimeLimit;
};

class SelectionSystem :
	public System
{
public:
	SelectionSystem(InputComponent* pInputComponent, FriedmannTimer* timer, double initialObjectRadius);
	virtual void Execute(double deltaTime) override;

	Entity* GetSelectedEntity();
	int GetSelectedIndex();

	std::vector<Entity*> GetEntities();
private:
	InputComponent* m_pInputComponent;
	Game& m_game;
	SphericalTransformComponent* m_pCameraTransform;
	SphericalCameraComponent* m_pCameraComponent;
	FriedmannTimer* m_pTimer;

	double m_initialObjectRadius;
	int m_selectedIndex = -1;
	Entity* m_pSelectedEntity = nullptr;
	double m_minDistance = 1000000.;
};

class RadiusUpdateSystem : public System {
public:
	RadiusUpdateSystem(FriedmannTimer * timer, SphericalRenderSystem * renderSystem, SphericalTransformComponent* cameraTransform);
	virtual void Execute(double deltaTime) override;

	double RadiusFunction(double mu);
private:
	FriedmannTimer* m_timer;
	SphericalRenderSystem* m_renderSystem;
	SphericalTransformComponent* m_cameraTransform;
	std::function<double(double)> m_radiusFunction; 
};

double CalculateFrequency(double distanceNormalized);

class SoundSystem : public System {
public:
	SoundSystem(SelectionSystem* pSelectionSystem, SphericalTransformComponent* pCameraTransform);
	virtual void Execute(double deltaTime) override;
private:
	DynamicSound* m_pSound;
	SelectionSystem* m_pSelectionSystem;
	SphericalTransformComponent* m_pCameraTransform;

	double m_currentChi;
	Entity* m_currentEntity = nullptr;

	bool m_hasObjectChanged = false;

	double m_oldRadius = -1.;
	bool m_hasRadiusChanged = true;
};


HWND CreateFriedmannWindow();

void DrawFriedmann(HDC hdc);

void UpdateFriedmannWindow(double time);
void DrawFriedmannPoint(HDC hdc);

double RayTraceSpherePos(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, double r_projected_sq);
double RayTraceSphereNeg(DirectX::SimpleMath::Vector4 sphericalPosition, DirectX::SimpleMath::Vector3 rayStart, DirectX::SimpleMath::Vector3 direction, DirectX::SimpleMath::Matrix view, double r_projected_sq);
double RayTraceSphereMouse(double mouseX, double mouseY, SphericalTransformComponent* pSphericalTransform, 
	DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, double r_sphere, double w_sphere, double mu, double initialObjectRadius);



FriedmannTimer* CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, SphericalTransformComponent * cameraTransform, SphericalRenderSystem* renderSystem, InputComponent * inputComponent, double initialObjectRadius,
	System ** controlSystem, System ** visibilitySystem, System ** radiusUpdateSystem, 
	System ** animationSystem, SelectionSystem ** selectionSystem, System ** soundSystem);

const int friedmann_w = 300, friedmann_h = 90;