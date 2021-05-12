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

    for (int i = 1; i <= stackCount - 1; i++) {
        auto phi = i * phiStep;
        for (int j = 0; j <= sliceCount; j++) {
            auto theta = j * thetaStep;
            XMFLOAT4 pos(
                (radius * sinf(phi) * cosf(theta)),
                (radius * cosf(phi)),
                (radius * sinf(phi) * sinf(theta)),
                1.f
            );

            auto uv = XMFLOAT2(theta / XM_2PI, phi / XM_PI);
            vertices.push_back({ pos,
                //pos.Normalize(псевдокод)
                uv });
        }
    }

    vertices.push_back({ XMFLOAT4(0.f, -radius, 0.f, 1.f),
        //XMFLOAT4(0.f, -1.f, 0.f, 0.f),    //normal
        XMFLOAT2(0.f, 1.f) }); //south pole

    //INDICES

    return nullptr;
}
