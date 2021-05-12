#include "pch.h"
#include "EuclideanMeshComponentFactory.h"

#include "MeshComponent.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

MeshComponent* EuclideanMeshComponentFactory::CreateSphere(double radius, int sliceCount, int stackCount)
{
    auto phiStep = XM_PI / stackCount;
    auto thetaStep = XM_2PI / sliceCount;



    return nullptr;
}
