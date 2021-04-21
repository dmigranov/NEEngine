#pragma once
#include "TransformComponent.h"
class SphericalTransformComponent :
    public TransformComponent
{
public:
    virtual void Move(DirectX::SimpleMath::Vector3 v) override;
    virtual void Move(double x, double y, double z) override;
    virtual void Rotate(DirectX::SimpleMath::Vector3 r) override;
    virtual void Rotate(double rx, double ry, double rz) override;
};

