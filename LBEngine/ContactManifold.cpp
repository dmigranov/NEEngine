#include "pch.h"
#include "ContactManifold.h"

using namespace DirectX::SimpleMath;

ContactManifold::ContactManifold(double penetration, DirectX::SimpleMath::Vector3 normal)
{
	m_normal = normal;
	m_penetration = penetration;
}

ContactManifold::ContactManifold()
{
	m_normal = Vector3::Zero;
	m_penetration = 0;
}
