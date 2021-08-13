#pragma once
#include "TransformComponent.h"
class HyperbolicTransformComponent :
    public TransformComponent
{
public:
    HyperbolicTransformComponent();
    HyperbolicTransformComponent(double x, double y, double z);
    HyperbolicTransformComponent(double x, double y, double z, double rx, double ry, double rz);
    HyperbolicTransformComponent(DirectX::SimpleMath::Vector3 position);
    HyperbolicTransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation);

private:
    double m_yaw = 0., m_pitch = 0., m_roll = 0.;


    DirectX::SimpleMath::Vector4 m_position;
};

