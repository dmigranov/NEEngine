#pragma once
#include "SphericalExpFogEffect.h"
class SphericalDopplerEffect :
    public SphericalExpFogEffect
{
public:
    struct PerApplicationPSConstantBufferDoppler 
    {
        DirectX::XMVECTORF32 fogColor = DirectX::Colors::CadetBlue;
        DirectX::XMVECTORF32 selectionColor = DirectX::Colors::GhostWhite;
        double velocity_coeff = 50000000.; //0
    };

    struct PerObjectPSConstantBuffer
    {
        bool isSelected = false;
    };

    struct PerApplicationVSConstantBufferDoppler
    {
        DirectX::XMMATRIX projFront;
        DirectX::XMMATRIX projBack;
        double density = 0.1;
        double radius = 1.;
        double radius_old = 1.;
        double deltaTime = 0.;
    };

    SphericalDopplerEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor);

    virtual bool Initialize() override;
    virtual void Deinitialize() override;

    virtual void UpdatePerObject(const Entity* pEntity, double deltaTime) override;

    virtual void Clean() override;

    void SetVelocity(double velocity);
    double GetVelocity();

    //virtual void SetRadius(double radius) override;

    virtual void SetFogColor(DirectX::XMVECTORF32 fogColor) override;



private:
    PerApplicationPSConstantBufferDoppler   perApplicationPSConstantBuffer;
    PerObjectPSConstantBuffer               perObjectPSConstantBuffer;
    PerApplicationVSConstantBufferDoppler   perApplicationVSConstantBufferDoppler;


    ID3D11Buffer* g_d3dPerObjectPSConstantBuffer = nullptr;

    static double m_radius_old;// = 1.;
};
