#include "pch.h"
#include "BitmapComponent.h"

#include "VertexTexMeshComponent.h"
#include "Game.h"

using namespace DirectX::SimpleMath;

BitmapComponent::BitmapComponent(unsigned int bitmapWidth, unsigned int bitmapHeight, bool isOpaque)
{
	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;
	m_spriteSheet = nullptr;
	m_isOpaque = isOpaque;

	auto& game = Game::GetInstance();
	auto device = game.GetDevice();

	InitializeBuffers(device);
}

BitmapComponent::BitmapComponent(unsigned int bitmapWidth, unsigned int bitmapHeight, Texture* pTexture, bool isOpaque) : BitmapComponent(bitmapWidth, bitmapHeight, isOpaque)
{
	SetTexture(pTexture);
}

BitmapComponent::~BitmapComponent()
{
	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}

	return;
}

void BitmapComponent::SetFrameIndex(unsigned int frameIndex)
{
	m_frameIndex = frameIndex;
}

void BitmapComponent::SetTexture(Texture* texture)
{
	m_spriteSheet = texture;
	m_texWidth = texture->GetWidth();
	m_texWidth = texture->GetHeight();
}

bool BitmapComponent::IsOpaque()
{
	return m_isOpaque;
}

bool BitmapComponent::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	DWORD* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;

	m_vertexCount = 6;

	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	//todo: на самом деле это не совсем правильно, там же в пикселях
	float widthDiv2 = m_bitmapWidth / 2.f, heightDiv2 = m_bitmapHeight / 2.f;

	// First triangle.
	vertices[0].position = Vector3(-widthDiv2, heightDiv2, 0.f);  // Top left.
	vertices[1].position = Vector3(widthDiv2, -heightDiv2, 0.f);  // Bottom right.
	vertices[2].position = Vector3(-widthDiv2, -heightDiv2, 0.f);  // Bottom left.

	// Second triangle.
	vertices[3].position = Vector3(-widthDiv2, heightDiv2, 0.f);  // Top left.
	vertices[4].position = Vector3(widthDiv2, heightDiv2, 0.f);  // Top right.
	vertices[5].position = Vector3(widthDiv2, -heightDiv2, 0.f);  // Bottom right.


	vertices[0].uv = Vector2(0.f, 0.f);
	vertices[1].uv = Vector2(1.f, 1.f);
	vertices[2].uv = Vector2(0.f, 1.f);

	vertices[3].uv = Vector2(0.f, 0.f);
	vertices[4].uv = Vector2(1.f, 0.f);
	vertices[5].uv = Vector2(1.f, 1.f);

	for (int i = 0; i < 6; i++)
		indices[i] = i;

	// Vertex Buffer
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;		//DYNAMIC!
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Index Buffer
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	m_pDevice = device;

	return true;
}

bool BitmapComponent::UpdateBuffers()
{
	//todo: обновить uv в зависимости от индекса
	//todo: dynamic buffers
	return false;
}
