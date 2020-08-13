#pragma once
class Force;

class Impulse
{
public:
	Impulse();
	Impulse(DirectX::SimpleMath::Vector3 vector);
	Impulse(DirectX::SimpleMath::Vector2 vector);
	static Impulse Zero;

	Force GetForce();

private:
	DirectX::SimpleMath::Vector3 m_impulseVector;
};