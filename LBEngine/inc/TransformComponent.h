#pragma once
#include "Component.h"
class TransformComponent :
    public Component
{
public:
    TransformComponent();
    TransformComponent(double x, double y, double z);
    TransformComponent(DirectX::SimpleMath::Vector3 position);
    TransformComponent(double x, double y, double z, double rx, double ry, double rz, double sx = 1, double sy = 1, double sz = 1);
    TransformComponent(DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 rotation, DirectX::SimpleMath::Vector3 scale);

    const DirectX::SimpleMath::Matrix& GetWorld();
    const DirectX::SimpleMath::Matrix& GetView();

    //todo: setPosition, Move, Rotate... В них ставить флаг

private:
    void Recalculate();
    void RecalculateView();


    TransformComponent* m_pParent;
    DirectX::SimpleMath::Matrix m_world;
    DirectX::SimpleMath::Vector3 m_positionLocal;
    DirectX::SimpleMath::Vector3 m_rotation;
    DirectX::SimpleMath::Vector3 m_scale;

    DirectX::SimpleMath::Vector3 m_position;

    DirectX::SimpleMath::Vector3 m_forward, m_right, m_up;

    DirectX::SimpleMath::Matrix m_view;


    bool m_shouldRecalcWorld;
    bool m_shouldRecalcView;

};

