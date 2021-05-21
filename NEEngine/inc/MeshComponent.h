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