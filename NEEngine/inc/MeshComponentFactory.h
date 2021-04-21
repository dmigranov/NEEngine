#pragma once

class MeshComponent;
class Game;

class MeshComponentFactory
{
public:
	template<class VertexData> MeshComponent* CreateMeshComponent(int nv, VertexData* vertices, int ni, WORD* indices) {
		auto& game = Game::GetInstance();
		auto device = game.GetDevice();
		auto deviceContext = game.GetDeviceContext(); //todo: оптимизировать

		ID3D11Buffer* g_d3dVertexBuffer = nullptr;
		ID3D11Buffer* g_d3dIndexBuffer = nullptr;

		D3D11_BUFFER_DESC vertexBufferDesc;
		ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

		vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  //how the buffer is bound to pipeline
		vertexBufferDesc.ByteWidth = sizeof(VertexData) * nv;
		vertexBufferDesc.CPUAccessFlags = 0;    // no CPU access is necessary
		vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

		//used to specify the data that is used to initialize a buffer when it is created.
		D3D11_SUBRESOURCE_DATA resourceData;
		ZeroMemory(&resourceData, sizeof(D3D11_SUBRESOURCE_DATA));
		resourceData.pSysMem = vertices; //A pointer to the data to initialize the buffer with.
		device->CreateBuffer(&vertexBufferDesc, &resourceData, &g_d3dVertexBuffer);

		// Create and initialize the index buffer.
		D3D11_BUFFER_DESC indexBufferDesc;
		ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));

		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		indexBufferDesc.ByteWidth = sizeof(WORD) * ni;
		indexBufferDesc.CPUAccessFlags = 0;
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		resourceData.pSysMem = indices;

		device->CreateBuffer(&indexBufferDesc, &resourceData, &g_d3dIndexBuffer);

		MeshComponent* returnMesh = new MeshComponent(g_d3dVertexBuffer, g_d3dIndexBuffer, typeid(VertexData));

		//todo: создать класс SphericalMeshComponentFactory 
		//его методы: создание по списку вершин и индексов,
		//но также и создание предопределнных объектов

		return returnMesh;
	}
};

