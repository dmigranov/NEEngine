#include "pch.h"
#include "RandomSpherical.h"


RandomSpherical::RandomSpherical(double radius) : m_gen(rd()), m_distr(-radius, radius)
{
	m_radius = radius;
}

DirectX::SimpleMath::Vector4 RandomSpherical::GeneratePoint()
{
	double x = m_distr(m_gen);
	double y = m_distr(m_gen);
	double z = m_distr(m_gen);
	double w = m_distr(m_gen);

	return DirectX::SimpleMath::Vector4();
}
