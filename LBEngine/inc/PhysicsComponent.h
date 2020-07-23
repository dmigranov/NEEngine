#pragma once
#include "Component.h"

#include <map>

class PhysicsComponent :
    public Component
{
public:
    PhysicsComponent();
    void AddForce(std::string forceName, DirectX::SimpleMath::Vector3 force);
    DirectX::SimpleMath::Vector3 GetForce(std::string forceName);
    void RemoveForce(std::string forceName);

private:
    DirectX::SimpleMath::Vector3 m_velocity;
    DirectX::SimpleMath::Vector3 m_acceleration;
    double m_mass;

    std::map<std::string, DirectX::SimpleMath::Vector3> m_forces;
};

