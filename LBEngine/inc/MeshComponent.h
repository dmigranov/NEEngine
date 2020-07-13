#pragma once

#include "Texture.h"
#include <wtypes.h>

#include "ResourceManager.h"

template <class T> class MeshComponent
{
public:
    MeshComponent(int nv, T* vertices, int ni, WORD* indices);
    virtual void Render()
    {

    }
	virtual ~MeshComponent()
    {

    }
    void SetTexture(Texture* texture)
    {
        this->m_pTexture = texture;
    }
protected:
    ID3D11Buffer* g_d3dVertexBuffer = nullptr;
    ID3D11Buffer* g_d3dIndexBuffer = nullptr;
    ID3D11DeviceContext* deviceContext;
    ID3D11Resource* d3dConstantBuffer;     //todo: буфферы должны быть в классе для Shader'а

    T* g_Vertices;
    int verticesCount;
    WORD* g_Indices;
    int indicesCount;

    Texture* m_pTexture;
};
