#include "pch.h"
#include "SphericalEllipsoid.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SphericalEllipsoid::SphericalEllipsoid(float a, float b, float c, int sliceCount, int stackCount, Texture* texture) : SphericalEllipsoid(a, b, c, sliceCount, stackCount, texture, Matrix::Identity)
{}

SphericalEllipsoid::SphericalEllipsoid(float a, float b, float c, int sliceCount, int stackCount, Texture* texture, DirectX::XMMATRIX world)
{
	auto phiStep = XM_PI / stackCount;
	auto thetaStep = XM_2PI / sliceCount;

	std::vector<VertexPosColor> vertices;
	std::vector<WORD> indices;

	XMFLOAT4 color(0, 0, 0, 0);
    float bInv = sqrtf(1.f - b * b);
	vertices.push_back({ XMFLOAT4(0.f, c, 0.f, bInv), color, XMFLOAT2(0.f, 0.f) });

    for (int i = 1; i <= stackCount - 1; i++) {
        auto phi = i * phiStep;
        float y = (b * cosf(phi));
        float phiSin = sinf(phi);
        for (int j = 0; j <= sliceCount; j++) {
            auto theta = j * thetaStep;
            float x = (a * phiSin * cosf(theta));
            float z = (c * phiSin * sinf(theta));
            float height = sqrtf(1 - x*x - y*y - z*z);

            XMFLOAT4 pos(
                x,
                y,
                z,
                height
            );

            auto uv = XMFLOAT2(theta / XM_2PI, phi / XM_PI);
            vertices.push_back({ pos, color, uv });
        }

    }

    vertices.push_back({ XMFLOAT4(0.f, -c, 0.f, bInv), color, XMFLOAT2(0.f, 1.f) });


    WORD northPoleIndex = 0;
    for (int i = 1; i <= sliceCount; i++) {
        indices.push_back(northPoleIndex);
        indices.push_back(i + 1);
        indices.push_back(i);
    }

    WORD baseIndex = 1;
    WORD ringVertexCount = sliceCount + 1;
    for (int i = 0; i < stackCount - 2; i++) {
        for (int j = 0; j < sliceCount; j++) {
            indices.push_back(baseIndex + i * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);

            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j);
            indices.push_back(baseIndex + i * ringVertexCount + j + 1);
            indices.push_back(baseIndex + (i + 1) * ringVertexCount + j + 1);

        }
    }

    WORD southPoleIndex = vertices.size() - 1;
    baseIndex = southPoleIndex - ringVertexCount;
    for (int i = 0; i < sliceCount; i++) {
        indices.push_back(southPoleIndex);
        indices.push_back(baseIndex + i);
        indices.push_back(baseIndex + i + 1);
    }

    m_texture = texture;

    g_Vertices = &vertices[0];
    verticesCount = vertices.size();

    g_Indices = &indices[0];
    indicesCount = indices.size();

    auto& game = Game::GetInstance();
    auto device = game.g_d3dDevice;
    deviceContext = game.g_d3dDeviceContext;
    d3dConstantBuffer = game.g_d3dVSConstantBuffers[2];

    // Create and initialize the vertex buffer.
    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  //how the buffer is bound to pipeline
    vertexBufferDesc.ByteWidth = sizeof(VertexPosColor) * verticesCount;
    vertexBufferDesc.CPUAccessFlags = 0;    // no CPU access is necessary
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

    //used to specify the data that is used to initialize a buffer when it is created.
    D3D11_SUBRESOURCE_DATA resourceData;
    ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
    resourceData.pSysMem = g_Vertices; //A pointer to the data to initialize the buffer with.

    device->CreateBuffer(&vertexBufferDesc, &resourceData, &g_d3dVertexBuffer);

    // Create and initialize the index buffer.
    D3D11_BUFFER_DESC indexBufferDesc;
    ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));

    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.ByteWidth = sizeof(WORD) * indicesCount;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    resourceData.pSysMem = g_Indices;

    constantBuffer.m_world = world;

    device->CreateBuffer(&indexBufferDesc, &resourceData, &g_d3dIndexBuffer);
}
