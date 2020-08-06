#include "pch.h"
#include "Force.h"
#include "..\inc\Force.h"

Force::Force(DirectX::SimpleMath::Vector3 vector)
{
	m_forceVector = vector;
}

Force::Force(DirectX::SimpleMath::Vector3 vector, std::function<void()> forceUpdater)
{
	m_forceVector = vector;
	m_forceUpdater = forceUpdater;
	m_hasToBeUpdated = true;
}

DirectX::SimpleMath::Vector3& Force::GetVector() noexcept
{
	return m_forceVector;
}

Force& Force::operator+=(const Force& V) noexcept
{
	m_forceVector += V.m_forceVector;
}

Force& Force::operator-=(const Force& V) noexcept
{
	m_forceVector -= V.m_forceVector;
}

Force Force::operator+(const Force& V1, const Force& V2) noexcept
{
	return Force(V1.m_forceVector + V2.m_forceVector);
}

Force Force::operator-(const Force& V1, const Force& V2) noexcept
{
	return Force(V1.m_forceVector - V2.m_forceVector);
}
