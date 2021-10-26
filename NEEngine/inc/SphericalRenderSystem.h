#pragma once
#include "System.h"
class SphericalRenderSystem :
    public System
{
public:
    SphericalRenderSystem(double radius = 1.);
    virtual void Execute(double deltaTime) override;

    void SetRadius(double radius);
private:
    void Render(Entity* pEntity, ID3D11DeviceContext* pDeviceContext);

    void UpdateOnRadiusChange();
    double m_radius;
};

