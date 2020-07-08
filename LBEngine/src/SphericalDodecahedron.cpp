#include "pch.h"
#include "SphericalDodecahedron.h"
#include "Game.h"

XMFLOAT4 SphericalDodecahedron::GenerateRandomColor()
{
    return XMFLOAT4(float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), float(rand()) / float(RAND_MAX), 1.f);
}

SphericalDodecahedron::SphericalDodecahedron(double wSec, XMMATRIX world) : SphericalDodecahedron(wSec)
{}

SphericalDodecahedron::SphericalDodecahedron(double section) 
{
    sectionHeight = section;

    double inv = sqrt(1. - section * section);
    double coeff = inv / sqrt(3.);
    double phi = 0.5 + sqrt(5) / 2.0;
    double pdc = phi / coeff;
    double ipdc = 1 / (phi * coeff);
    std::cout << sqrt(pdc * pdc + ipdc * ipdc + section * section) << std::endl;    //21 - я ошибся!

    SphericalMesh::VertexPosColor vertices[] = {
        { XMFLOAT4(coeff,  coeff, coeff, section), GenerateRandomColor() }, // 0
        { XMFLOAT4(coeff,  coeff, -coeff, section), GenerateRandomColor() }, // 1
        { XMFLOAT4(coeff, -coeff, coeff, section), GenerateRandomColor() }, // 2
        { XMFLOAT4(coeff, -coeff, -coeff, section), GenerateRandomColor() }, // 3
        { XMFLOAT4(-coeff, coeff, coeff, section), GenerateRandomColor() }, // 4
        { XMFLOAT4(-coeff, coeff, -coeff, section), GenerateRandomColor() }, // 5
        { XMFLOAT4(-coeff, -coeff, coeff, section), GenerateRandomColor() }, // 6
        { XMFLOAT4(-coeff, -coeff, -coeff, section), GenerateRandomColor() }, // 7

        { XMFLOAT4(0,  pdc, ipdc, section), GenerateRandomColor() }, // 8
        { XMFLOAT4(0,  pdc, -ipdc, section), GenerateRandomColor() }, // 9
        { XMFLOAT4(0,  -pdc, ipdc, section), GenerateRandomColor() }, // 10
        { XMFLOAT4(0,  -pdc, -ipdc, section), GenerateRandomColor() }, // 11

        { XMFLOAT4(pdc, ipdc, 0, section), GenerateRandomColor() }, // 12
        { XMFLOAT4(pdc, -ipdc, 0, section), GenerateRandomColor() }, // 13
        { XMFLOAT4(-pdc, ipdc, 0, section), GenerateRandomColor() }, // 14
        { XMFLOAT4(-pdc, -ipdc, 0, section), GenerateRandomColor() }, // 15
        };


    g_Vertices = vertices;
    verticesCount = _countof(vertices);

    WORD indices[] = {
             0, 8, 10,
             0, 10, 12,
             12, 10, 2

            
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

    constantBuffer.m_world = Matrix::Identity;
}


void SphericalDodecahedron::SetSectionHeight(double newSectionHeight)
{
    //todo
}

double SphericalDodecahedron::GetSectionHeight()
{
    //todo
    return 0.0;
}

