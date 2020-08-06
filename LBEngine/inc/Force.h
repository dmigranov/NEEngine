#pragma once
class Force
{
public:
    Force();
    Force(DirectX::SimpleMath::Vector3 vector);
    Force(DirectX::SimpleMath::Vector3 vector, std::function<void()> forceUpdater);
    static Force Zero;
    DirectX::SimpleMath::Vector3& GetVector() noexcept;

    //todo: переопределение
    Force& operator+= (const Force& V) noexcept;
    Force& operator-= (const Force& V) noexcept;
    friend Force operator+(const Force& V1, const Force& V2) noexcept
    {
        return Force(V1.m_forceVector + V2.m_forceVector);
    }
    friend Force operator-(const Force& V1, const Force& V2) noexcept
    {
        return Force(V1.m_forceVector - V2.m_forceVector);
    }
    void Update();
private:
    DirectX::SimpleMath::Vector3 m_forceVector;
    std::function<void()> m_forceUpdater;
    bool m_hasToBeUpdated = false;
};

