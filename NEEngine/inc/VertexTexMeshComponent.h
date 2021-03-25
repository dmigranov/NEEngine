#pragma once

#include "Texture.h"
#include <wtypes.h>

#include "Component.h"
#include "MeshComponent.h"

struct VertexPosTex //todo: �������������
{
    DirectX::XMFLOAT4 Position;  //���������� ����� � ������������� ������������
    DirectX::XMFLOAT2 TexCoord;
};

class VertexTexMeshComponent : public MeshComponent<VertexPosTex>
{
public:

    VertexTexMeshComponent(int nv, VertexPosTex* vertices, int ni, WORD* indices);

protected:
    /*
    * 
    * 
    ID3D11Buffer* g_d3dVertexBuffer = nullptr;
    ID3D11Buffer* g_d3dIndexBuffer = nullptr;
    ID3D11DeviceContext* deviceContext;
    ID3D11Resource* d3dConstantBuffer;     //todo: ������� ������ ���� � ������ ��� Effect!

    VertexPosTex* g_Vertices;
    int verticesCount;
    WORD* g_Indices;
    int indicesCount;

    Texture* m_pTexture;    //todo: ��������� � ��������
    
    
    */
};
