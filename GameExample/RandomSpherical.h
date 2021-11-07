#pragma once
class RandomSpherical
{
public:
	RandomSpherical(double radius);
	DirectX::SimpleMath::Vector4 GeneratePoint();
private: 
	double m_radius;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen;
};

