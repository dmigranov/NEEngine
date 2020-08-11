#pragma once
class Impulse
{
public:
	Impulse();
	Impulse(DirectX::SimpleMath::Vector3 vector);
	Impulse(DirectX::SimpleMath::Vector2 vector);
	static Impulse Zero;

private:
	DirectX::SimpleMath::Vector3 m_impulseVector;
};