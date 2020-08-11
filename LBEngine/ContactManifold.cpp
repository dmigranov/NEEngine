#include "pch.h"
#include "ContactManifold.h"

ContactManifold::ContactManifold(double penetration, DirectX::SimpleMath::Vector3 normal)
{
	m_normal = normal;
	m_penetration = penetration;
}
