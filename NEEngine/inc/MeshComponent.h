#pragma once

class Game;

template <class VertexData>
class MeshComponent : public Component
{
public:
	MeshComponent(int nv, VertexData* vertices, int ni, WORD* indices);

	//todo: СТАРОЕ! Должно быть потом удалено, так как это должно быть на системе
	virtual void Render(DirectX::XMMATRIX world);

	virtual ~MeshComponent();
	void SetTexture(Texture* texture);

protected:
	ID3D11Buffer* g_d3dVertexBuffer = nullptr;
	ID3D11Buffer* g_d3dIndexBuffer = nullptr;
	ID3D11DeviceContext* deviceContext;
	ID3D11Resource* d3dConstantBuffer;     //todo: буфферы должны быть в классе для Effect!

	VertexData* g_Vertices;
	int verticesCount;
	WORD* g_Indices;
	int indicesCount;

	Texture* m_pTexture;    //todo: перенести в материал
};

template<class VertexData>
inline MeshComponent<VertexData>::MeshComponent(int nv, VertexData* vertices, int ni, WORD* indices)
{
	auto& game = Game::GetInstance();
	auto device = game.GetDevice();
	deviceContext = game.GetDeviceContext();
	d3dConstantBuffer = game.GetVSConstantBuffers()[2];
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
inline void MeshComponent<VertexData>::Render(DirectX::XMMATRIX world)
{
	const UINT vertexStride = sizeof(VertexData);   //Each stride is the size (in bytes) of the elements that are to be used from that vertex buffer.
	const UINT offset = 0;
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->IASetVertexBuffers(0, 1, &g_d3dVertexBuffer, &vertexStride, &offset);
	deviceContext->IASetIndexBuffer(g_d3dIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	if (m_pTexture != nullptr)
	{     //Pixel Shader Stafe - unique 4 every stage
		auto shaderResource = m_pTexture->GetTexture();
		deviceContext->PSSetShaderResources(0, 1, &shaderResource);
	}

	deviceContext->UpdateSubresource(d3dConstantBuffer, 0, nullptr, &world, 0, 0);

	//DRAW
	deviceContext->DrawIndexed(indicesCount, 0, 0);
}

template<class VertexData>
inline MeshComponent<VertexData>::~MeshComponent()
{
	SafeRelease(g_d3dVertexBuffer);
	SafeRelease(g_d3dIndexBuffer);
}

template<class VertexData>
inline void MeshComponent<VertexData>::SetTexture(Texture* texture)
{
	this->m_pTexture = texture;
}
