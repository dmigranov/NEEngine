#pragma once
#include "Component.h"

class Game;
class Effect;

class MeshComponent : public Component
{
	friend class MeshComponentFactory;

public:

	Effect* GetEffect() const;
	void SetEffect(Effect* effect);

	ID3D11Buffer * GetVertexBuffer() const;
	ID3D11Buffer * GetIndexBuffer() const;
	D3D_PRIMITIVE_TOPOLOGY GetTopology() const;
	unsigned int GetIndicesCount();

	const std::type_info& GetVertexDataType();

	virtual ~MeshComponent();

	void* GetAdditionalData();
	void SetAdditionalData(void * data);

protected:
	MeshComponent(ID3D11Buffer* g_d3dVertexBuffer, ID3D11Buffer* g_d3dIndexBuffer, const std::type_info& vertexDataType, unsigned int indicesCount, D3D_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	ID3D11Buffer* g_d3dVertexBuffer = nullptr;
	ID3D11Buffer* g_d3dIndexBuffer = nullptr;
	D3D_PRIMITIVE_TOPOLOGY m_topology;
	unsigned int m_indicesCount = 0;
	Effect* m_pEffect;

	const std::type_info& m_vertexDataType;

	void* m_additionalData = nullptr;
};