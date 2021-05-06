#pragma once
#include "MeshComponentFactory.h"
class SphericalMeshComponentFactory :
    public MeshComponentFactory
{
public:
    static MeshComponent* CreateSphericalSphere(double radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color = {1.f, 1.f, 1.f, 1.f});
    static MeshComponent* CreateSphericalMeshFromFile(); //todo
    //todo: создание из списка вершин и индексов, но с проверкой корректности вершин
};

