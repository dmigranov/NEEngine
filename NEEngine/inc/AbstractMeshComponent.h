#pragma once
#include "Component.h"

class Effect;
class Texture;

class AbstractMeshComponent : public Component
{
	friend class SphericalRenderSystem; //todo: исправить?


public:
	Effect* GetEffect() const;
	void SetEffect(Effect * effect);

protected:
	ID3D11Buffer* g_d3dVertexBuffer = nullptr;
	ID3D11Buffer* g_d3dIndexBuffer = nullptr;

	ID3D11DeviceContext* deviceContext;

	int indicesCount;

	Effect* m_pEffect;

};