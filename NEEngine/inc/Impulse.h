#pragma once
class Force;

class Impulse
{
public:
	Impulse();
	Impulse(DirectX::SimpleMath::Vector3 vector);
	Impulse(DirectX::SimpleMath::Vector2 vector);

    DirectX::SimpleMath::Vector3& GetVector() noexcept;

	static Impulse Zero;
    Impulse& operator+= (const Impulse& V) noexcept;
    Impulse& operator-= (const Impulse& V) noexcept;
    friend Impulse operator+(const Impulse& V1, const Impulse& V2) noexcept
    {
        return Impulse(V1.m_impulseVector + V2.m_impulseVector);
    }
    friend Impulse operator-(const Impulse& V1, const Impulse& V2) noexcept
    {
        return Impulse(V1.m_impulseVector - V2.m_impulseVector);
    }

private:
	DirectX::SimpleMath::Vector3 m_impulseVector;
};