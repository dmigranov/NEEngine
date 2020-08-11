#include "pch.h"
#include "Impulse.h"

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
