#pragma once
#include "CameraComponent.h"
class HyperbolicCameraComponent :
    public CameraComponent
{
    HyperbolicCameraComponent();

    virtual const DirectX::XMMATRIX& GetProj() override;


};

