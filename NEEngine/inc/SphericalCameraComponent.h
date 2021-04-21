#pragma once
#include "CameraComponent.h"
class SphericalCameraComponent :
    public CameraComponent
{
public:
    virtual const DirectX::XMMATRIX& GetProj() override;
    const DirectX::XMMATRIX& GetFrontSphericalProj() const;
    const DirectX::XMMATRIX& GetBackSphericalProj() const;
    const DirectX::XMMATRIX& GetEllipticProj() const;
private:
    virtual void RecalculateProj() override;

    DirectX::SimpleMath::Matrix backProj;
    DirectX::SimpleMath::Matrix frontProj;
    DirectX::SimpleMath::Matrix ellProj;

};

