#pragma once
#include "Component.h"

#include <map>

class PhysicsComponent :
    public Component
{
public:
    PhysicsComponent(double mass);
    void AddForce(std::string forceName, DirectX::SimpleMath::Vector3 force);
    DirectX::SimpleMath::Vector3 GetForce(std::string forceName);
    void RemoveForce(std::string forceName);

    void SetAcceleration(DirectX::SimpleMath::Vector3 a);
    void SetVelocity(DirectX::SimpleMath::Vector3 v);

    const DirectX::SimpleMath::Vector3& GetVelocity();
    const DirectX::SimpleMath::Vector3& GetAcceleration();
    const double& GetMass();


private:
    friend class PhysicsSystem;
    DirectX::SimpleMath::Vector3 m_velocity;
    DirectX::SimpleMath::Vector3 m_acceleration;
    double m_mass;

    std::map<std::string, DirectX::SimpleMath::Vector3> m_forces;
};

