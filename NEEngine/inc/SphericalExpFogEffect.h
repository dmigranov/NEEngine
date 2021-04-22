#pragma once
#include "Effect.h"

class Game;
class Texture;

class SphericalExpFogEffect :
    public Effect
{
public:
    struct VertexData
    {
        DirectX::XMFLOAT4 Position;  //координаты точки в четырехмерном пространстве
        DirectX::XMFLOAT2 TexCoord;
    };

    struct PerApplicationVSConstantBuffer
    {
        DirectX::XMMATRIX projFront;
        DirectX::XMMATRIX projBack;
        double density = 0.5;
        double pad;
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
        DirectX::XMVECTORF32 mistColor = DirectX::Colors::CadetBlue;
        float m_edgeThickness = 0.00f;
    };

    SphericalExpFogEffect(Texture* pTexture, double fogDensity);

    // ”наследовано через Effect

    virtual bool Initialize() override;
    virtual void Deinitialize() override;

    virtual void UpdatePerObject(const Entity* pEntity) override;
    virtual void UpdatePerScene() override;             //todo: impl
    virtual void UpdatePerApplication() override;       //todo: impl

    virtual unsigned int GetVertexBufferSize() const override;
    virtual const std::type_info& GetVertexDataType() override;

    ~SphericalExpFogEffect();

private:
    static bool isSpherical;

    PerApplicationPSConstantBuffer perApplicationPSConstantBuffer;
    PerApplicationVSConstantBuffer perApplicationVSConstantBuffer;
    double density = 0.01;

    ID3D11InputLayout* g_d3dInputLayout = nullptr;

    ID3D11VertexShader* g_d3dVertexShaderSph = nullptr;
    ID3D11PixelShader* g_d3dPixelShader = nullptr;

    ID3D11SamplerState* g_d3dSamplerState = nullptr;

    Texture* m_pTexture = nullptr;
    double m_fogDensity = 0;

    //ID3D11Buffer* g_d3dVSConstantBuffer; //тк у каждого объекта свой эффект то только один
    enum ConstantBuffer
    {
        CB_Application, //The application level constant buffer stores variables that rarely change. 
        CB_Frame,       //The frame level constant buffer stores variables that change each frame. An example of a frame level shader variable would be the cameraТs view matrix which changes whenever the camera moves
        CB_Object,      //The object level constant buffer stores variables that are different for every object being rendered. An example of an object level shader variable is the objectТs world matrix.
        NumConstantBuffers
    };
    //three constant buffers: buffers are used to store shader variables that remain constant during current draw call. An example of a constant shader variable is the cameraТs projection matrix. Since the projection matrix will be the same for every vertex of the object, this variable does not need to be passed to the shader using vertex data.
    
    ID3D11Buffer* g_d3dVSConstantBuffers[NumConstantBuffers];

    ID3D11Buffer* g_d3dPSConstantBuffer = nullptr;

    Game& game;// = Game::GetInstance();

};

