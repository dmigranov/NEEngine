#include "pch.h"
#include "SphericalCube.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

XMFLOAT4 SphericalCube::GenerateRandomColor()
{
    return XMFLOAT4(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), 1.f);
}

SphericalCube::SphericalCube(double wSec) : SphericalCube(wSec, Matrix::Identity)
{
}

SphericalCube::SphericalCube(double wSec, XMMATRIX world) : SphericalCube(wSec, Matrix::Identity, nullptr)
{
}

SphericalCube::SphericalCube(double wSec, XMFLOAT4* colors) : SphericalCube(wSec, Matrix::Identity, colors)
{
}

SphericalCube::SphericalCube(double wSec, XMMATRIX world, XMFLOAT4* colors)
{
    //fixed coord - всегда w!

    if (colors == nullptr)
    {
        colors = new XMFLOAT4[8];
        for (int i = 0; i < 8; i++)
            colors[i] = GenerateRandomColor();
    }

    double cubeCoord = sqrt((1 - wSec * wSec)/3.f);
    SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(-cubeCoord,  -cubeCoord, -cubeCoord, wSec), colors[0] }, // 0
        { XMFLOAT4(-cubeCoord,  -cubeCoord, cubeCoord, wSec), colors[1]  }, // 1
        { XMFLOAT4(-cubeCoord,  cubeCoord, -cubeCoord, wSec), colors[2]  }, // 2
        { XMFLOAT4(-cubeCoord,  cubeCoord, cubeCoord, wSec), colors[3]  }, // 3
        { XMFLOAT4(cubeCoord,  -cubeCoord, -cubeCoord, wSec), colors[4]  }, // 4
        { XMFLOAT4(cubeCoord,  -cubeCoord, cubeCoord, wSec), colors[5]  }, // 5
        { XMFLOAT4(cubeCoord,  cubeCoord, -cubeCoord, wSec), colors[6]  }, // 6
        { XMFLOAT4(cubeCoord,  cubeCoord, cubeCoord, wSec), colors[7]  }, // 7
    };
    g_Vertices = vertices;
    verticesCount = _countof(vertices);

    if (wSec < 0)
        world *= Matrix(1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, -1, 0,
            0, 0, 0, 1);

    WORD indices[] = {
            0, 2, 4,
            4, 2, 6,

            0, 1, 2,
            3, 2, 1,

            4, 7, 5,
            4, 6, 7,

            2, 3, 7,
            2, 7, 6,

            1, 0, 4,
            1, 4, 5,

            7, 3, 1,
            5, 7, 1
    };


    auto& game = Game::GetInstance();
    auto device = game.g_d3dDevice;
    deviceContext = game.g_d3dDeviceContext;
    d3dConstantBuffer = game.g_d3dVSConstantBuffers[2];
    g_Indices = indices;

    indicesCount = _countof(indices);

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

    device->CreateBuffer(&indexBufferDesc, &resourceData, &g_d3dIndexBuffer);

    constantBuffer.m_world = world;
}
