#pragma once
#include "Component.h"
class TransformComponent :
    public Component
{
public:
    TransformComponent();
    TransformComponent(double x, double y, double z);
    TransformComponent(DirectX::SimpleMath::Vector3 position);

private:
    void Recalculute();

    TransformComponent* m_pParent;
    DirectX::SimpleMath::Matrix worldMatrix;
    DirectX::SimpleMath::Vector3 m_position;
    bool m_shouldRecalc;
};

