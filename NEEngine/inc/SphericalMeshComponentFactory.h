#pragma once
#include "MeshComponentFactory.h"
class SphericalMeshComponentFactory :
    public MeshComponentFactory
{
public:
    MeshComponent* CreateSphericalSphere(double radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color = {1.f, 1.f, 1.f, 1.f});
    MeshComponent* CreateSphericalMeshFromFile(); //todo
};

