#pragma once
class Force
{
public:
    Force(DirectX::SimpleMath::Vector3 vector);
    Force(DirectX::SimpleMath::Vector3 vector, std::function<void()> forceUpdater);
private:
    DirectX::SimpleMath::Vector3 m_forceVector;
    std::function<void()> m_forceUpdater;
    bool m_hasToBeUpdated = false;
};

