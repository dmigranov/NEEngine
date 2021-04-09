#pragma once
#include "CameraComponent.h"
class SphericalCameraComponent :
    public CameraComponent
{
    virtual const DirectX::XMMATRIX& GetProj() override;
    const DirectX::XMMATRIX& GetFrontSphericalProj() const;
    const DirectX::XMMATRIX& GetBackSphericalProj() const;
    const DirectX::XMMATRIX& GetEllipticProj() const;


};

