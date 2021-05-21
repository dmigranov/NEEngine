#pragma once

class Game;
class Effect;
//todo: убрать шаблон, сгрузить работу на MeshComponentFactory

//template <class VertexData>
class MeshComponent : public Component
{
	friend class MeshComponentFactory;

public:

	Effect* GetEffect() const;
	void SetEffect(Effect* effect);

	ID3D11Buffer * const GetVertexBuffer();
	ID3D11Buffer * const GetIndexBuffer();
	unsigned int GetIndicesCount();

	const std::type_info& GetVertexDataType();

	virtual ~MeshComponent();
protected:
	MeshComponent(ID3D11Buffer* g_d3dVertexBuffer, ID3D11Buffer* g_d3dIndexBuffer, const std::type_info& vertexDataType, unsigned int indicesCount);
	ID3D11Buffer* g_d3dVertexBuffer = nullptr;
	ID3D11Buffer* g_d3dIndexBuffer = nullptr;
	unsigned int m_indicesCount = 0;
	Effect* m_pEffect;

	const std::type_info& m_vertexDataType;

};

/*
inline MeshComponent<VertexData>::MeshComponent(int nv, VertexData* vertices, int ni, WORD* indices)
{
	auto& game = Game::GetInstance();
	auto device = game.GetDevice();
	deviceContext = game.GetDeviceContext();
	g_Indices = indices;
	g_Vertices = vertices;
	verticesCount = nv;
	indicesCount = ni;

	// Create and initialize the vertex buffer.
	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  //how the buffer is bound to pipeline
	vertexBufferDesc.ByteWidth = sizeof(VertexData) * verticesCount;
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
}

template<class VertexData>
inline MeshComponent<VertexData>::~MeshComponent()
{
	SafeRelease(g_d3dVertexBuffer);
	SafeRelease(g_d3dIndexBuffer);
}

*/