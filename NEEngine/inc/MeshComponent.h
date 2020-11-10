#pragma once

#include "Texture.h"
#include <wtypes.h>

#include "Component.h"


class MeshComponent : public Component
{
public:
    struct VertexPosTex //todo: затемплейтить
    {
        DirectX::XMFLOAT4 Position;  //координаты точки в четырехмерном пространстве
        DirectX::XMFLOAT2 TexCoord;
    };

    MeshComponent(int nv, VertexPosTex* vertices, int ni, WORD* indices);
    virtual void Render(DirectX::XMMATRIX world);

    virtual ~MeshComponent();

    void SetTexture(Texture* texture);
protected:
    ID3D11Buffer* g_d3dVertexBuffer = nullptr;
    ID3D11Buffer* g_d3dIndexBuffer = nullptr;
    ID3D11DeviceContext* deviceContext;
    ID3D11Resource* d3dConstantBuffer;     //todo: буфферы должны быть в классе для Shader'а

    VertexPosTex* g_Vertices;
    int verticesCount;
    WORD* g_Indices;
    int indicesCount;

    Texture* m_pTexture;    //todo: перенести в материал
};
