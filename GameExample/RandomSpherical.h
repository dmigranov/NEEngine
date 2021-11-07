#pragma once
#include <random>

class RandomSphericalGenerator
{
public:
	RandomSphericalGenerator(double radius);
	DirectX::SimpleMath::Vector4 GeneratePoint();
private: 
	double m_radius, m_radius_square;
	double epsilon = 0.001;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 m_gen;
	std::uniform_real_distribution<> m_distr;
};