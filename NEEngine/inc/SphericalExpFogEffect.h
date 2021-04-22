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
        DirectX::XMFLOAT4 Position;  //���������� ����� � ������������� ������������
        DirectX::XMFLOAT2 TexCoord;
    };

    struct PerApplicationVSConstantBuffer
    {
        DirectX::SimpleMath::Matrix proj;
        double density;
        double pad;
    };

    struct PerFrameVSConstantBuffer
    {
        DirectX::SimpleMath::Matrix view;
    };

    struct PerObjectVSConstantBuffer
    {
        DirectX::SimpleMath::Matrix world;
    };

    struct PerApplicationPSConstantBuffer
    {
        DirectX::XMVECTORF32 mistColor = DirectX::Colors::CadetBlue;
        float m_edgeThickness = 0.00f;
    };

    SphericalExpFogEffect(Texture* pTexture, double fogDensity);

    // ������������ ����� Effect

    virtual bool Initialize() override;
    virtual void Deinitialize() override;

    virtual void UpdatePerObject(const Entity* pEntity) override;
    virtual void UpdatePerScene() override;
    virtual void UpdatePerApplication() override;

    virtual unsigned int GetVertexBufferSize() const override;
    virtual const std::type_info& GetVertexDataType() override;

    ~SphericalExpFogEffect();

private:
    PerApplicationPSConstantBuffer perApplicationPSConstantBuffer;
    PerApplicationVSConstantBuffer perApplicationVSConstantBuffer;

    ID3D11InputLayout* g_d3dInputLayout = nullptr;

    ID3D11VertexShader* g_d3dVertexShaderSph = nullptr;
    ID3D11PixelShader* g_d3dPixelShader = nullptr;

    ID3D11SamplerState* g_d3dSamplerState = nullptr;

    Texture* m_pTexture = nullptr;
    double m_fogDensity = 0;

    //ID3D11Buffer* g_d3dVSConstantBuffer; //�� � ������� ������� ���� ������ �� ������ ����
    enum ConstantBuffer
    {
        CB_Application, //The application level constant buffer stores variables that rarely change. 
        CB_Frame,       //The frame level constant buffer stores variables that change each frame. An example of a frame level shader variable would be the camera�s view matrix which changes whenever the camera moves
        CB_Object,      //The object level constant buffer stores variables that are different for every object being rendered. An example of an object level shader variable is the object�s world matrix.
        NumConstantBuffers
    };
    //three constant buffers: buffers are used to store shader variables that remain constant during current draw call. An example of a constant shader variable is the camera�s projection matrix. Since the projection matrix will be the same for every vertex of the object, this variable does not need to be passed to the shader using vertex data.
    
    ID3D11Buffer* g_d3dVSConstantBuffers[NumConstantBuffers];

    ID3D11Buffer* g_d3dPSConstantBuffer = nullptr;

    Game& game;// = Game::GetInstance();

};

