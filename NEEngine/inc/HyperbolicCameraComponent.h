#pragma once
#include "CameraComponent.h"
class HyperbolicCameraComponent :
    public CameraComponent
{
public:
    HyperbolicCameraComponent();

    virtual const DirectX::XMMATRIX& GetProj() override;
};

