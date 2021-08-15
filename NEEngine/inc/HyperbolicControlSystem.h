#pragma once
#include "ActionSystem.h"

#include "Entity.h"
#include "InputComponent.h"
#include "HyperbolicTransformComponent.h"
#include "HyperbolicCameraComponent.h"

class HyperbolicControlSystem :
    public ActionSystem<InputComponent, HyperbolicTransformComponent, HyperbolicCameraComponent>
{
public:
	HyperbolicControlSystem(double movementSpeed, double rotationSpeed);
private:
	DirectX::SimpleMath::Vector4 spherePos = DirectX::SimpleMath::Vector4(0, 0, 0, 1);


	double pitchDelta = 0., yawDelta = 0.;
	double m_yaw = 0., m_pitch = 0.;
	double m_pitchLimit = DirectX::XM_PI / 2.0 - 0.01;

	DirectX::SimpleMath::Matrix R = DirectX::SimpleMath::Matrix::Identity,
		RYaw = DirectX::SimpleMath::Matrix::Identity,
		RPitch = DirectX::SimpleMath::Matrix::Identity,
		RRoll = DirectX::SimpleMath::Matrix::Identity; // represents camera orientation

};

