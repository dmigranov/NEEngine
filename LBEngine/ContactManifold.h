#pragma once
class ContactManifold
{
public:
	ContactManifold(double penetration, DirectX::SimpleMath::Vector3 normal);
	double m_penetration;
	DirectX::SimpleMath::Vector3 m_normal;
};

