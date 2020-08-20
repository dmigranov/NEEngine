#pragma once

class Entity;

class ContactManifold
{
public:
	ContactManifold();
	ContactManifold(Entity * p1, Entity * p2);
private:
	friend class CollisionSystem;

	double m_penetration;
	DirectX::SimpleMath::Vector3 m_normal;

	Entity *m_pEntity1 = nullptr, *m_pEntity2 = nullptr;
};

