#pragma once
#include "System.h"
class ToricRenderSystem :
    public System
{
public:
    ToricRenderSystem();
    virtual void Execute(double deltaTime) override;
private:
    void Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext);
};

