#include "pch.h"
#include "SphericalMeshComponentFactory.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

MeshComponent* SphericalMeshComponentFactory::CreateSphericalSphere(double radius, int sliceCount, int stackCount)
{
	int triCount = 0;

	auto phiStep = XM_PI / stackCount;
	auto thetaStep = XM_2PI / sliceCount;

	std::vector<VertexData> vertices;
	std::vector<WORD> indices;

	double height = sqrt(1.f - (radius * radius));

	vertices.push_back({ XMFLOAT4(0.f, radius, 0.f, height), XMFLOAT2(0.f, 0.f) });	//North pole

    for (int i = 1; i <= stackCount - 1; i++) {
        auto phi = i * phiStep;
        for (int j = 0; j <= sliceCount; j++) {
            auto theta = j * thetaStep;
            XMFLOAT4 pos(
                (radius * sinf(phi) * cosf(theta)),
                (radius * cosf(phi)),
                (radius * sinf(phi) * sinf(theta)),
                height
            );

            auto uv = XMFLOAT2(theta / XM_2PI, phi / XM_PI);
            vertices.push_back({ pos, uv });
        }
    }

    vertices.push_back({ XMFLOAT4(0.f, -radius, 0.f, height), XMFLOAT2(0.f, 1.f) });



	return nullptr;
}

MeshComponent* SphericalMeshComponentFactory::CreateSphericalMeshFromFile()
{
	return nullptr;
}
