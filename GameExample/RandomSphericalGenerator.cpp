#include "pch.h"
#include "RandomSphericalGenerator.h"


RandomSphericalGenerator::RandomSphericalGenerator(double radius) : m_gen(rd()), m_distr(-radius, radius)
{
	m_radius = radius;
	m_radius_square = radius * radius;
}

DirectX::SimpleMath::Vector4 RandomSphericalGenerator::GeneratePoint()
{
generate:
	double x = m_distr(m_gen);
	double y = m_distr(m_gen);
	double z = m_distr(m_gen);
	double w = m_distr(m_gen);

	double norm_square = x * x + y * y + z * z + w * w;

	if (norm_square < epsilon || norm_square > m_radius_square) //too close too zero OR outside the sphere
		goto generate;

	//todo: normalize

	return DirectX::SimpleMath::Vector4();
}
