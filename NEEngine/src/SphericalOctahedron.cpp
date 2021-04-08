#include "pch.h"
#include "SphericalOctahedron.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

XMFLOAT4 GenerateRandomColor()
{
    return XMFLOAT4(float(rand())/float(RAND_MAX), float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), 1.f);
}

SphericalOctahedron::SphericalOctahedron(double wSec, XMMATRIX world) : SphericalOctahedron(FixedCoordinate::FC_W, wSec, world)
{}

SphericalOctahedron::SphericalOctahedron(double wSec) : SphericalOctahedron(wSec, XMMatrixIdentity())
{}

SphericalOctahedron::SphericalOctahedron(double wSec, XMMATRIX world, XMFLOAT4 * colors) : SphericalOctahedron(FixedCoordinate::FC_W, wSec, world, colors)
{}

SphericalOctahedron::SphericalOctahedron(double wSec, XMFLOAT4* colors) : SphericalOctahedron(wSec, Matrix::Identity, colors)
{}

SphericalOctahedron::SphericalOctahedron(FixedCoordinate coord, double section, XMMATRIX world)
{
    this->fc = coord;
    sectionHeight = section;

    double inv = sqrt(1. - section * section);
    if (coord == FixedCoordinate::FC_W)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(0.f,  0.f, -inv, section), GenerateRandomColor() }, // 0
        { XMFLOAT4(0.f,  0.f, inv, section), GenerateRandomColor() }, // 1
        { XMFLOAT4(0.f, -inv, 0.f, section), GenerateRandomColor() }, // 2
        { XMFLOAT4(0.f,  inv, 0.f, section), GenerateRandomColor() }, // 3
        { XMFLOAT4(-inv,  0.f, 0.f, section), GenerateRandomColor() }, // 4
        { XMFLOAT4(inv,  0.f, 0.f, section), GenerateRandomColor() }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);

        if (section < 0)
            world *= Matrix(1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, -1, 0,
                0, 0, 0, 1);   //матрица отражения!
    }
    else if (coord == FixedCoordinate::FC_Z)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(0.f,  0.f, section, -inv), GenerateRandomColor() }, // 0
        { XMFLOAT4(0.f,  0.f, section, inv), GenerateRandomColor() }, // 1
        { XMFLOAT4(0.f, -inv, section, 0.f), GenerateRandomColor() }, // 2
        { XMFLOAT4(0.f,  inv, section, 0.f), GenerateRandomColor() }, // 3
        { XMFLOAT4(-inv,  0.f, section, 0.f), GenerateRandomColor()}, // 4
        { XMFLOAT4(inv,  0.f, section, 0.f), GenerateRandomColor() }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);
    }
    else if (coord == FixedCoordinate::FC_Y)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(0.f, section, 0.f, -inv), GenerateRandomColor() }, // 0
        { XMFLOAT4(0.f, section, 0.f, inv), GenerateRandomColor() }, // 1
        { XMFLOAT4(0.f, section, -inv, 0.f), GenerateRandomColor() }, // 2
        { XMFLOAT4(0.f, section, inv, 0.f), GenerateRandomColor() }, // 3
        { XMFLOAT4(-inv, section, 0.f, 0.f), GenerateRandomColor() }, // 4
        { XMFLOAT4(inv, section, 0.f, 0.f), GenerateRandomColor() }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);
    }
    else //if (coord == FixedCoordinate::FC_X)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(section, 0.f, 0.f, -inv), GenerateRandomColor() }, // 0
        { XMFLOAT4(section, 0.f, 0.f, inv), GenerateRandomColor() }, // 1
        { XMFLOAT4(section, 0.f, -inv, 0.f), GenerateRandomColor() }, // 2
        { XMFLOAT4(section, 0.f, inv, 0.f), GenerateRandomColor() }, // 3
        { XMFLOAT4(section, -inv, 0.f, 0.f), GenerateRandomColor() }, // 4
        { XMFLOAT4(section, inv, 0.f, 0.f), GenerateRandomColor() }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);
    }

    WORD indices[] = {
            0, 2, 4,
            4, 3, 0,
            5, 2, 0,
            0, 3, 5,
            4, 2, 1,
            1, 3, 4,
            1, 2, 5,
            5, 3, 1,
    };

    auto& game = Game::GetInstance();
    auto device = game.g_d3dDevice;
    deviceContext = game.g_d3dDeviceContext;
    //d3dConstantBuffer = game.g_d3dVSConstantBuffers[2];
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

SphericalOctahedron::SphericalOctahedron(FixedCoordinate coord, double section) : SphericalOctahedron(coord, section, XMMatrixIdentity())
{
}

SphericalOctahedron::SphericalOctahedron(FixedCoordinate coord, double section, XMMATRIX world, XMFLOAT4* colors)
{
    this->fc = coord;
    sectionHeight = section;

    double inv = sqrt(1. - section * section);
    if (coord == FixedCoordinate::FC_W)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(0.f,  0.f, -inv, section), colors[0] }, // 0
        { XMFLOAT4(0.f,  0.f, inv, section), colors[1]  }, // 1
        { XMFLOAT4(0.f, -inv, 0.f, section), colors[2]  }, // 2
        { XMFLOAT4(0.f,  inv, 0.f, section), colors[3]  }, // 3
        { XMFLOAT4(-inv,  0.f, 0.f, section), colors[4]  }, // 4
        { XMFLOAT4(inv,  0.f, 0.f, section), colors[5]  }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);

        if (section < 0)
            world*=Matrix(1,0,0,0,
                0,1,0,0,
                0,0,-1,0,
                0,0,0,1);   //матрица отражения!
    }
    else if (coord == FixedCoordinate::FC_Z)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(0.f,  0.f, section, -inv),colors[0]  }, // 0
        { XMFLOAT4(0.f,  0.f, section, inv), colors[1] }, // 1
        { XMFLOAT4(0.f, -inv, section, 0.f), colors[2] }, // 2
        { XMFLOAT4(0.f,  inv, section, 0.f), colors[3] }, // 3
        { XMFLOAT4(-inv,  0.f, section, 0.f), colors[4]}, // 4
        { XMFLOAT4(inv,  0.f, section, 0.f), colors[5] }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);
    }
    else if (coord == FixedCoordinate::FC_Y)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(0.f, section, 0.f, -inv), colors[0] }, // 0
        { XMFLOAT4(0.f, section, 0.f, inv), colors[1] }, // 1
        { XMFLOAT4(0.f, section, -inv, 0.f), colors[2] }, // 2
        { XMFLOAT4(0.f, section, inv, 0.f), colors[3] }, // 3
        { XMFLOAT4(-inv, section, 0.f, 0.f), colors[4] }, // 4
        { XMFLOAT4(inv, section, 0.f, 0.f), colors[5] }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);
    }
    else //if (coord == FixedCoordinate::FC_X)
    {
        SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(section, 0.f, 0.f, -inv), colors[0]  }, // 0
        { XMFLOAT4(section, 0.f, 0.f, inv), colors[1] }, // 1
        { XMFLOAT4(section, 0.f, -inv, 0.f), colors[2] }, // 2
        { XMFLOAT4(section, 0.f, inv, 0.f), colors[3] }, // 3
        { XMFLOAT4(section, -inv, 0.f, 0.f), colors[4] }, // 4
        { XMFLOAT4(section, inv, 0.f, 0.f), colors[5] }, // 5
        };
        g_Vertices = vertices;
        verticesCount = _countof(vertices);
    }

    WORD indices[] = {
            0, 2, 4,
            4, 3, 0,
            5, 2, 0,
            0, 3, 5,
            4, 2, 1,
            1, 3, 4,
            1, 2, 5,
            5, 3, 1,
    };

    auto& game = Game::GetInstance();
    auto device = game.g_d3dDevice;
    deviceContext = game.g_d3dDeviceContext;
    //d3dConstantBuffer = game.g_d3dVSConstantBuffers[2];
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

void SphericalOctahedron::SetSectionHeight(double newSectionHeight)
{
    if (newSectionHeight < -1 || newSectionHeight > 1)
        return;

    double multiplier = sqrt((1. - newSectionHeight * newSectionHeight) / (1. - sectionHeight * sectionHeight));;
    switch (fc)
    {
    case FixedCoordinate::FC_X:
        constantBuffer.m_world = Matrix(newSectionHeight / sectionHeight, 0, 0, 0,
            0, multiplier, 0, 0,
            0, 0, multiplier, 0,
            0, 0, 0, multiplier) * constantBuffer.m_world;
        break;
    case FixedCoordinate::FC_Y:
        constantBuffer.m_world = Matrix(multiplier, 0, 0, 0,
            0, newSectionHeight / sectionHeight, 0, 0,
            0, 0, multiplier, 0,
            0, 0, 0, multiplier) * constantBuffer.m_world;
        break;
    case FixedCoordinate::FC_Z:
        constantBuffer.m_world = Matrix(multiplier, 0, 0, 0,
            0, multiplier, 0, 0,
            0, 0, newSectionHeight / sectionHeight, 0,
            0, 0, 0, multiplier) * constantBuffer.m_world;
        break;
    case FixedCoordinate::FC_W:
        constantBuffer.m_world = Matrix(multiplier, 0, 0, 0,
            0, multiplier, 0, 0,
            0, 0, multiplier, 0,
            0, 0, 0, newSectionHeight / sectionHeight) * constantBuffer.m_world;

        break;
    }
    sectionHeight = newSectionHeight;

}

double SphericalOctahedron::GetSectionHeight()
{
    return sectionHeight;
}
