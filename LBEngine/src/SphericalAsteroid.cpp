#include "pch.h"


#include "SphericalAsteroid.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SphericalAsteroid::SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color)
    : SphericalAsteroid(amplitude, radius, sliceCount, stackCount, color, Matrix::Identity)
{}

SphericalAsteroid::SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color, DirectX::XMMATRIX world)
{
    srand(time(NULL));


    dist = std::uniform_real_distribution<>(-amplitude, amplitude);

    auto phiStep = XM_PI / stackCount;
    auto thetaStep = XM_2PI / sliceCount;

    std::vector<VertexPosColor> vertices;
    std::vector<WORD> indices;

    float height = sqrtf(1.f - (radius * radius));

    vertices.push_back({ XMFLOAT4(0.f, radius, 0.f, height), color, XMFLOAT2(0.f, 0.f) });

    for (int i = 1; i <= stackCount - 1; i++) {
        auto phi = i * phiStep;
        Vector4 posSaved;

        for (int j = 0; j <= sliceCount; j++) {
            auto theta = j * thetaStep;
            XMFLOAT4 pos(
                (radius * sinf(phi) * cosf(theta)),
                (radius * cosf(phi)),
                (radius * sinf(phi) * sinf(theta)),
                height
            );

            int transformChoice = rand() % 3;
            Vector4 posTransformed = XMVector4Transform((Vector4)pos, transformChoice == 0 ? SphericalRotationXW(dist(engine)) : transformChoice == 1 ? SphericalRotationYW(dist(engine)) : SphericalRotationZW(dist(engine)));
            pos = posTransformed;
            if (j == 0)
                posSaved = pos;
            else if (j == sliceCount)
                pos = posSaved;

            auto uv = XMFLOAT2(theta / XM_2PI, phi / XM_PI);
            vertices.push_back({ pos, color, uv });
        }

    }

    vertices.push_back({ XMFLOAT4(0.f, -radius, 0.f, height), color, XMFLOAT2(0.f, 1.f) });

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

SphericalAsteroid::SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, Texture* texture)
    : SphericalAsteroid(amplitude, radius, sliceCount, stackCount, texture, Matrix::Identity)
{}

SphericalAsteroid::SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, Texture* texture, DirectX::XMMATRIX world)
    : SphericalAsteroid(amplitude, radius, sliceCount, stackCount, XMFLOAT4(0.f, 0.f, 0.f, 1.f), world)
{
    m_texture = texture;
}

