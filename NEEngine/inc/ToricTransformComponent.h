#pragma once
#include "TransformComponent.h"
class ToricTransformComponent :
    public TransformComponent
{
public:
    ToricTransformComponent();
    ToricTransformComponent(double x, double y, double z);
    ToricTransformComponent(DirectX::SimpleMath::Vector3 position);
    ToricTransformComponent(double x, double y, double z, double rx, double ry, double rz, double sx = 1, double sy = 1, double sz = 1);
    ToricTransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);

    virtual void Move(DirectX::SimpleMath::Vector3 v) override;
    virtual void Move(double x, double y, double z) override;

    //virtual void Recalculate() override;
    //virtual void RecalculateView() override;

    static void SetTorusDimensions(double tX, double tY, double tZ);
private:
    void Normalize();

    static double m_torX, m_torY, m_torZ;
};

