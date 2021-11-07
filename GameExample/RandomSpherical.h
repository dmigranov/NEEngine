#pragma once
class RandomSpherical
{
public:
	RandomSpherical(double radius);
	DirectX::SimpleMath::Vector4 GeneratePoint();
};

