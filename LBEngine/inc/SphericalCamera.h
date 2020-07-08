#pragma once
#include "Camera.h"
#include "SphericalMath.h"

class SphericalCamera :
	public Camera
{
public:
	SphericalCamera();
	const DirectX::XMMATRIX& GetView() override;
	const DirectX::XMMATRIX& GetAntipodalView();
	const DirectX::XMMATRIX& GetProj() override;
	const DirectX::XMMATRIX& GetFrontProj();
	const DirectX::XMMATRIX& GetBackProj();
	const DirectX::XMMATRIX& GetEllipticalProj();
	const DirectX::XMMATRIX& GetCameraTransform() override;


	DirectX::SimpleMath::Vector4 GetPosition() override;
	void Move(DirectX::SimpleMath::Vector3 v) override;
	void ChangePitchYawRoll(double deltaPitch, double deltaYaw, double deltaRoll) override;


private:
	DirectX::SimpleMath::Vector4 spherePos = DirectX::SimpleMath::Vector4(0, 0, 0, 1);
	DirectX::SimpleMath::Vector3 dV = DirectX::SimpleMath::Vector3(0, 0, 0);
	double pitchDelta = 0, yawDelta = 0;
	double pitchLimit = DirectX::XM_PI / 2.0f - 0.01f;

	DirectX::SimpleMath::Matrix T = DirectX::SimpleMath::Matrix::Identity; // represents the translation of the camera in world space
	DirectX::SimpleMath::Matrix R = DirectX::SimpleMath::Matrix::Identity, RInv = DirectX::SimpleMath::Matrix::Identity, RYaw = DirectX::SimpleMath::Matrix::Identity, RPitch = DirectX::SimpleMath::Matrix::Identity, RRoll = DirectX::SimpleMath::Matrix::Identity; // represents camera orientation
	DirectX::SimpleMath::Quaternion RotationQuaternion;
	DirectX::XMFLOAT3 GetSphericalFromCartesian(float x4, float x3, float x2, float x1);
};

