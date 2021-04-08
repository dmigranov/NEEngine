#pragma once
#include "System.h"
class SphericalRenderSystem :
    public System
{
public:
    SphericalRenderSystem();
    virtual void Execute(double deltaTime) override;
private:
    void Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext);
};

