#include "pch.h"
#include "ContactManifold.h"

using namespace DirectX::SimpleMath;

ContactManifold::ContactManifold(Entity* p1, Entity* p2) : ContactManifold()
{
	m_pEntity1 = p1;
	m_pEntity2 = p2;
}

ContactManifold::ContactManifold()
{
	m_normal = Vector3::Zero;
	m_penetration = 0;
}
