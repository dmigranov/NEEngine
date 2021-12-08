#pragma once
#include "System.h"
class HyperbolicRenderSystem :
    public System
{
public:
    HyperbolicRenderSystem();
    virtual void Execute(double deltaTime) override;
private:
    void Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext, double deltaTime);
};

