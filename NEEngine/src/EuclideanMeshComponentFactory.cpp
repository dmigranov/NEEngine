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

    std::vector<VertexData> vertices;
    std::vector<WORD> indices;

    vertices.push_back({ XMFLOAT4(0.f, radius, 0.f, 1.f),
        //XMFLOAT4(0.f, 1.f, 0.f, 0.f),     //normal
        XMFLOAT2(0.f, 0.f) });	//North pole

    return nullptr;
}
