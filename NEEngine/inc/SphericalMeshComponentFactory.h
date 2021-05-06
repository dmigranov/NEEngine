#pragma once
#include "MeshComponentFactory.h"
class SphericalMeshComponentFactory :
    public MeshComponentFactory
{
public:

    struct VertexData
    {
        DirectX::XMFLOAT4 Position;  //координаты точки в четырехмерном пространстве
        //DirectX::XMFLOAT4 Normal;
        //DirectX::XMFLOAT4 Tangent; //нужно ли?
        DirectX::XMFLOAT2 TexCoord;
    };

    static MeshComponent* CreateSphericalSphere(double radius, int sliceCount, int stackCount);
    static MeshComponent* CreateSphericalMeshFromFile(); //todo
    //todo: создание из списка вершин и индексов, но с проверкой корректности вершин
};

