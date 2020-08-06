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
