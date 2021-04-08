#include "pch.h"
#include "Mesh.h"
#include "Game.h"

using namespace DirectX;

Mesh::Mesh()
{
}

Mesh::Mesh(int nv, VertexPosColor* vertices, int ni, WORD* indices) : Mesh(nv, vertices, ni, indices, XMMatrixIdentity())
{}


Mesh::Mesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, XMMATRIX world)
{
    auto& game = Game::GetInstance();
    auto device = game.g_d3dDevice;
    deviceContext = game.g_d3dDeviceContext;
    //d3dConstantBuffer = game.g_d3dVSConstantBuffers[2];
    g_Indices = indices;
    g_Vertices = vertices;
    verticesCount = nv;
    indicesCount = ni;

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

Mesh::~Mesh()
{
    SafeRelease(g_d3dIndexBuffer);
    SafeRelease(g_d3dVertexBuffer);
}

XMMATRIX Mesh::GetWorldMatrix()
{
    if (parentMesh == nullptr)
        return constantBuffer.m_world;
    else
        return constantBuffer.m_world * parentMesh->GetWorldMatrix();
}

void Mesh::SetWorldMatrix(XMMATRIX world)
{
	constantBuffer.m_world = world;
}

void Mesh::SetConstants(MeshConstantBuffer constantBuffer)
{
	this->constantBuffer = constantBuffer;
}

void Mesh::SetTexture(Texture* texture)
{
    this->m_texture = texture;
}

void Mesh::SetParent(Mesh* parent)
{
	parentMesh = parent;
}

void Mesh::AddUpdater(MeshUpdater updater)
{
	meshUpdaters.push_back(updater);
}

void Mesh::Update(float deltaTime)
{
	for (auto updater : meshUpdaters)
	{
		constantBuffer.m_world = updater(constantBuffer.m_world, deltaTime);
	}
}

Mesh::MeshUpdater::MeshUpdater(std::function<DirectX::SimpleMath::Matrix(DirectX::SimpleMath::Matrix, float delta)> func)
{
    m_func = func;
}

DirectX::SimpleMath::Matrix Mesh::MeshUpdater::operator()(DirectX::SimpleMath::Matrix in, float delta)
{
    return m_func(in, delta);
}

