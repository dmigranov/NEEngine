#pragma once
#include "CameraComponent.h"
class SphericalCameraComponent :
    public CameraComponent
{
public:
    SphericalCameraComponent();

    virtual const DirectX::XMMATRIX& GetProj() override;
    const DirectX::XMMATRIX& GetFrontSphericalProj();
    const DirectX::XMMATRIX& GetBackSphericalProj();
    const DirectX::XMMATRIX& GetEllipticProj();
private:
    virtual void RecalculateProj() override;

    DirectX::SimpleMath::Matrix m_backProj;
    DirectX::SimpleMath::Matrix m_frontProj;
    DirectX::SimpleMath::Matrix m_ellProj;

};

