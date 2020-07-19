#include "pch.h"
#include "BitmapComponent.h"

#include "MeshComponent.h"
#include "Game.h"

BitmapComponent::BitmapComponent(unsigned int width, unsigned int height, bool isOpaque)
{
	m_bitmapWidth = width;
	m_bitmapHeight = height;
	m_spriteSheet = nullptr;
	m_isOpaque = isOpaque;

	auto& game = Game::GetInstance();
	auto device = game.g_d3dDevice;

	InitializeBuffers(device);

}

BitmapComponent::BitmapComponent(unsigned int width, unsigned int height, Texture* texture, bool isOpaque) : BitmapComponent(width, height, isOpaque)
{
	SetTexture(texture);
}

BitmapComponent::~BitmapComponent()
{
	//delete ...
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

	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Load the index array with data.
	for (i = 0; i < m_indexCount; i++)
	{
		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;		//DYNAMIC!
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;
	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}



	return true;
}
