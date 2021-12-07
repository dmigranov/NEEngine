#pragma once
#include "SphericalEffect.h"
class SphericalDopplerEffect :
    public SphericalEffect
{
    struct PerApplicationVSConstantBuffer
    {
        DirectX::XMMATRIX projFront;
        DirectX::XMMATRIX projBack;
        double density = 0.1;
        double radius = 1.;
    };

    struct PerFrameVSConstantBuffer
    {
        DirectX::XMMATRIX view;
    };

    struct PerObjectVSConstantBuffer
    {
        DirectX::XMMATRIX world;
    };

    struct PerApplicationPSConstantBuffer
    {
        DirectX::XMVECTORF32 fogColor = DirectX::Colors::CadetBlue;
        double velocity;
    };

    SphericalDopplerEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor);


};

