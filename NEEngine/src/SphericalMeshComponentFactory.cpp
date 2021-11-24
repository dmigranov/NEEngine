#include "pch.h"
#include "SphericalMeshComponentFactory.h"

#include "MeshComponent.h"
#include "Game.h"

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

	vertices.push_back({ XMFLOAT4(0.f, radius, 0.f, height),
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
                height
            );

            auto uv = XMFLOAT2(theta / XM_2PI, phi / XM_PI);
            vertices.push_back({ pos,
                //pos,       //так как это сфера! нормализовывать не нужно, так как и так радиус пространства 1 (но если сферическое пространство произвольного радиуса, то нужно)
                uv });
        }
    }

    vertices.push_back({ XMFLOAT4(0.f, -radius, 0.f, height), 
        //XMFLOAT4(0.f, -1.f, 0.f, 0.f),    //normal
        XMFLOAT2(0.f, 1.f) }); //south pole

    //INDICES

    WORD northPoleIndex = 0;
    for (int i = 1; i <= sliceCount; i++) {
        indices.push_back(northPoleIndex);
        indices.push_back(i + 1);
        indices.push_back(i);
        triCount++;
    }

    WORD baseIndex = 1;
    WORD ringVertexCount = sliceCount + 1;
    for (int i = 0; i < stackCount - 2; i++) {
        for (int j = 0; j < sliceCount; j++) {
            indices.push_back(baseIndex + i * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            triCount++;

            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);
            triCount++;

        }
    }

    WORD southPoleIndex = vertices.size() - 1;
    baseIndex = southPoleIndex - ringVertexCount;
    for (int i = 0; i < sliceCount; i++) {
        indices.push_back(southPoleIndex);
        indices.push_back(baseIndex + i);
        indices.push_back(baseIndex + i + 1);
        triCount++;
    }

    auto g_Vertices = &vertices[0];
    auto verticesCount = vertices.size();

    auto g_Indices = &indices[0];
    auto indicesCount = indices.size();

    return MeshComponentFactory::CreateMeshComponent<VertexData>(verticesCount, g_Vertices, indicesCount, g_Indices);
}

MeshComponent* SphericalMeshComponentFactory::CreateSphericalPoint()
{
    VertexData* g_Vertices = new VertexData[1];
    g_Vertices[0] = { XMFLOAT4(0.f, 0.f, 0.f, 1.f), XMFLOAT2(0.f, 0.f)}; 

    WORD* g_Indices = new WORD[1]{0};

    return MeshComponentFactory::CreateMeshComponent<VertexData>(1, g_Vertices, 1, g_Indices, D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
}

MeshComponent* SphericalMeshComponentFactory::CreateSphericalMeshFromFile(std::string fileName)
{
	return nullptr;
}
