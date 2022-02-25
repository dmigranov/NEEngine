#pragma once
#include "System.h"

class InputComponent;
class SphericalTransformComponent;

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
	double m_initialObjectRadius;

};

