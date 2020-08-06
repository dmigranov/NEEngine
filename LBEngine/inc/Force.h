#pragma once
class Force
{
public:
    Force(DirectX::SimpleMath::Vector3 vector);
    Force(DirectX::SimpleMath::Vector3 vector, std::function<void()> forceUpdater);
    static Force Zero;
    DirectX::SimpleMath::Vector3& GetVector() noexcept;

    //todo: переопределение
    Force& operator+= (const Force& V) noexcept;
    Force& operator-= (const Force& V) noexcept;
    static Force operator+ (const Force& V1, const Force& V2) noexcept;
    static Force operator- (const Force& V1, const Force& V2) noexcept;
private:
    DirectX::SimpleMath::Vector3 m_forceVector;
    std::function<void()> m_forceUpdater;
    bool m_hasToBeUpdated = false;
};

Force Force::Zero = Force(DirectX::SimpleMath::Vector3::Zero);