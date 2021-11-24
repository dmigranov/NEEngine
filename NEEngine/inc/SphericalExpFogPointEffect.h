#pragma once
#include "SphericalExpFogEffect.h"
class SphericalExpFogPointEffect :
    public SphericalExpFogEffect
{
    SphericalExpFogPointEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor);

    virtual bool Initialize() override;
    virtual void Deinitialize() override;

    virtual void UpdatePerObject(const Entity* pEntity) override;
};

