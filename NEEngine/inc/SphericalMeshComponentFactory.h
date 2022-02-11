#pragma once
#include "MeshComponentFactory.h"

enum class SphericalVisibility {
    VISIBLE_NONE,
    VISIBLE_FRONT,
    VISIBLE_BACK,           //not really necessary but why not
    VISIBLE_ALL
};

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
    static MeshComponent* CreateSphericalPoint();
    static MeshComponent* CreateSphericalMeshFromFile(std::string fileName);
    //todo: создание из списка вершин и индексов, но с проверкой корректности вершин

private:
    static void SetVisibility();
};

