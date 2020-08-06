#include "pch.h"
#include "Force.h"

Force Force::Zero = Force(DirectX::SimpleMath::Vector3::Zero);

Force::Force() : Force(DirectX::SimpleMath::Vector3::Zero)
{}

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
	return *this;
}

Force& Force::operator-=(const Force& V) noexcept
{
	m_forceVector -= V.m_forceVector;
	return *this;
}

void Force::Update()
{
	if(m_hasToBeUpdated)
		m_forceUpdater();
}
