#pragma once
#include "SphericalExpFogEffect.h"
class SphericalExpFogPointEffect :
    public SphericalExpFogEffect
{
public:
    SphericalExpFogPointEffect(double fogDensity, DirectX::XMVECTORF32 fogColor);

    virtual bool Initialize() override;
    virtual void Deinitialize() override;

    virtual void UpdatePerObject(const Entity* pEntity, double deltaTime) override;

    virtual void Clean() override;
private:
    ID3D11GeometryShader* g_d3dGeometryShader = nullptr;

};

