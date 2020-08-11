#pragma once
#include "Component.h"

#include <map>

class Force;
class Impulse;

class PhysicsComponent :
    public Component
{
public:
    PhysicsComponent(double mass);

    void AddForce(std::string forceName, Force force);
    Force GetForce(std::string forceName);
    void RemoveForce(std::string forceName);

    void AddImpulse(std::string forceName, Impulse force);
    Impulse GetImpulse(std::string forceName);
    void RemoveImpulse(std::string forceName);

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

    std::map<std::string, Force> m_forces;
    std::map<std::string, Impulse> m_impulses;

};

