#pragma once
#include "Effect.h"

class Game;
class Texture;

class HyperbolicExpFogEffect :
    public Effect
{
public:

    //todo: structs

    struct PerApplicationPSConstantBuffer
    {
        DirectX::XMVECTORF32 fogColor = DirectX::Colors::CadetBlue;
    };

    HyperbolicExpFogEffect(Texture* pTexture, double fogDensity, DirectX::XMVECTORF32 fogColor);
    
    virtual bool Initialize() override;
    virtual void Deinitialize() override;

    virtual void UpdatePerObject(const Entity* pEntity) override;
    virtual void UpdatePerScene() override;             //todo: impl
    virtual void UpdatePerApplication() override;       //todo: impl

    virtual unsigned int GetVertexBufferSize() const override;
    virtual const std::type_info& GetVertexDataType() override;

    void SetFogColor(DirectX::XMVECTORF32 fogColor);

    ~HyperbolicExpFogEffect();

private:
    PerApplicationPSConstantBuffer perApplicationPSConstantBuffer;


    Game& game;
};

