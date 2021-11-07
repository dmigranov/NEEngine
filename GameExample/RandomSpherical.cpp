#include "pch.h"
#include "RandomSpherical.h"


RandomSpherical::RandomSpherical(double radius) : m_gen(rd()), m_distr(-radius, radius)
{
	m_radius = radius;
	m_radius_square = radius * radius;
}

DirectX::SimpleMath::Vector4 RandomSpherical::GeneratePoint()
{
	double x = m_distr(m_gen);
	double y = m_distr(m_gen);
	double z = m_distr(m_gen);
	double w = m_distr(m_gen);

	double norm_square = x * x + y * y + z * z + w * w;

	//if ()

	return DirectX::SimpleMath::Vector4();
}
