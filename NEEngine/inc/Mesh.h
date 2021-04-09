#pragma once

#include "Texture.h"

//todo" ”ƒјЋ»“№!

class Mesh
{
public:
    class MeshUpdater
    {
    public:
        MeshUpdater(std::function<DirectX::SimpleMath::Matrix(DirectX::SimpleMath::Matrix, float delta)> func);
        DirectX::SimpleMath::Matrix operator()(DirectX::SimpleMath::Matrix in, float delta);
    private:
        std::function<DirectX::SimpleMath::Matrix(DirectX::SimpleMath::Matrix, float delta)> m_func;
    };

    struct MeshConstantBuffer	//=Object Constant Buffer
    {
        DirectX::XMMATRIX m_world;
    };


    // Vertex data
    struct VertexPosColor
    {
        DirectX::XMFLOAT4 Position;  //координаты точки в четырехмерном пространстве
        DirectX::XMFLOAT4 Color;
        DirectX::XMFLOAT2 TexCoord;
    };

    Mesh();
    Mesh(int nv, VertexPosColor* vertices, int ni, WORD* indices);
    Mesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world);

    ~Mesh();

    DirectX::XMMATRIX GetWorldMatrix();
    void SetWorldMatrix(DirectX::XMMATRIX world);
    void SetConstants(MeshConstantBuffer constantBuffer);
    void SetTexture(Texture* texture);

    void SetParent(Mesh* parent);

    void AddUpdater(MeshUpdater updater);
    void Update(float deltaTime);

    virtual void Render(std::list<DirectX::XMMATRIX> matrices) = 0;
    virtual void Render() = 0;
    virtual void Render(DirectX::XMMATRIX matrix) = 0;


protected:
    ID3D11Buffer* g_d3dVertexBuffer = nullptr;
    ID3D11Buffer* g_d3dIndexBuffer = nullptr;
    ID3D11DeviceContext* deviceContext;
    ID3D11Resource* d3dConstantBuffer;

    VertexPosColor* g_Vertices;
    int verticesCount;
    WORD* g_Indices;
    int indicesCount;

    std::list<MeshUpdater> meshUpdaters;

    Mesh* parentMesh = nullptr;
    MeshConstantBuffer constantBuffer;

    Texture* m_texture;

};

