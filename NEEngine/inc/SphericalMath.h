#pragma once

DirectX::SimpleMath::Matrix BananaProjectionMatrix(double z0);
DirectX::SimpleMath::Matrix BananaProjectionMatrix(double fovY, double aspect, double z0);

DirectX::SimpleMath::Matrix BananaProjectionMatrixFrontHalf(double z0);
DirectX::SimpleMath::Matrix BananaProjectionMatrixFrontHalf(double fovY, double aspect, double z0);

DirectX::SimpleMath::Matrix BananaProjectionMatrixBackHalf(double z0);
DirectX::SimpleMath::Matrix BananaProjectionMatrixBackHalf(double fovY, double aspect, double z0);

DirectX::SimpleMath::Matrix SphericalRotationZW(float d);
DirectX::SimpleMath::Matrix SphericalRotationXW(float d);
DirectX::SimpleMath::Matrix SphericalRotationYW(float d);
DirectX::SimpleMath::Matrix SphericalRotationYZ(float d);
DirectX::SimpleMath::Matrix SphericalRotationXZ(float d);
DirectX::SimpleMath::Matrix SphericalRotationXY(float d);

float SphericalDistance(DirectX::SimpleMath::Vector4 vec1, DirectX::SimpleMath::Vector4 vec2, double radius);

DirectX::XMFLOAT3 GetSphericalFromCartesian(float x4, float x3, float x2, float x1);