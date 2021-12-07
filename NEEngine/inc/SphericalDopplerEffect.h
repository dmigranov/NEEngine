#pragma once
#include "SphericalExpFogEffect.h"
class SphericalDopplerEffect :
    public SphericalExpFogEffect
{
public:
    struct PerApplicationPSConstantBufferDoppler
    {
        DirectX::XMVECTORF32 fogColor = DirectX::Colors::CadetBlue;
        double velocity = 0; // 200000000.;
    };

    SphericalDopplerEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor);

    virtual bool Initialize() override;
    virtual void Deinitialize() override;

    virtual void UpdatePerObject(const Entity* pEntity) override;

    virtual void Clean() override;

private:

};

