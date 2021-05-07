#pragma once

#include "ActionSystem.h"

class InputComponent;
class SphericalTransformComponent;
class SphericalCameraComponent;

class SphericalControlSystem 
	: public ActionSystem<InputComponent, SphericalTransformComponent, SphericalCameraComponent>
{
public:
	SphericalControlSystem(double movementSpeed, double rotationSpeed);
private:
	DirectX::SimpleMath::Vector4 spherePos = DirectX::SimpleMath::Vector4(0, 0, 0, 1);


	double pitchDelta = 0, yawDelta = 0;
	double pitchLimit = DirectX::XM_PI / 2.0f - 0.01f;

	DirectX::SimpleMath::Matrix T = DirectX::SimpleMath::Matrix::Identity; // represents the translation of the camera in world space
	DirectX::SimpleMath::Matrix R = DirectX::SimpleMath::Matrix::Identity, 
								RInv = DirectX::SimpleMath::Matrix::Identity, 
								RYaw = DirectX::SimpleMath::Matrix::Identity, 
								RPitch = DirectX::SimpleMath::Matrix::Identity, 
								RRoll = DirectX::SimpleMath::Matrix::Identity; // represents camera orientation

};

