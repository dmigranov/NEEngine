#pragma once
#include "MeshComponentFactory.h"
class HyperbolicMeshComponentFactory :
    public MeshComponentFactory
{
public:
    struct VertexData
    {
        DirectX::XMFLOAT4 Position;
        //DirectX::XMFLOAT4 Normal;
        //DirectX::XMFLOAT4 Tangent; //нужно ли?
        DirectX::XMFLOAT2 TexCoord;
    };
};

