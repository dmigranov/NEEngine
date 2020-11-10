#include "pch.h"
#include "Impulse.h"
#include "Force.h"

Impulse Impulse::Zero = Impulse(DirectX::SimpleMath::Vector3::Zero);

Impulse::Impulse() : Impulse(DirectX::SimpleMath::Vector3::Zero) {}

Impulse::Impulse(DirectX::SimpleMath::Vector3 vector)
{
	m_impulseVector = vector;
}

Impulse::Impulse(DirectX::SimpleMath::Vector2 vector)
{
	m_impulseVector = DirectX::SimpleMath::Vector3(vector.x, vector.y, 0.);
}

DirectX::SimpleMath::Vector3& Impulse::GetVector() noexcept
{
	return m_impulseVector;
}

Impulse& Impulse::operator+=(const Impulse& V) noexcept
{
	m_impulseVector += V.m_impulseVector;
	return *this;
}

Impulse& Impulse::operator-=(const Impulse& V) noexcept
{
	m_impulseVector -= V.m_impulseVector;
	return *this;
}
