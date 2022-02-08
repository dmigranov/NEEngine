#include "pch.h"
#include "SphericalEffect.h"


bool SphericalEffect::m_isSpherical = true;
double SphericalEffect::m_radius = 0;

void SphericalEffect::SetMode(bool isSpherical)
{
	m_isSpherical = isSpherical;
}

void SphericalEffect::SetRadius(double radius)
{
	m_radius = radius;
}
