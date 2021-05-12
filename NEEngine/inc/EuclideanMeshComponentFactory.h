#pragma once
#include "MeshComponentFactory.h"
class EuclideanMeshComponentFactory :
    public MeshComponentFactory
{
    struct VertexData
    {
        DirectX::XMFLOAT4 Position;
        //DirectX::XMFLOAT4 Normal;
        //DirectX::XMFLOAT4 Tangent; //нужно ли?
        DirectX::XMFLOAT2 TexCoord;
    };

    static MeshComponent* CreateSphere(double radius, int sliceCount = 30, int stackCount = 30);
    static MeshComponent* CreateSphericalMeshFromFile(std::string fileName);
};

