#pragma once
#include "Component.h"

class Effect;
class Texture;

class AbstractMeshComponent : public Component
{
	friend class SphericalRenderSystem; //todo: исправить?


public:
	//todo: СТАРОЕ! Должно быть потом удалено, так как это должно быть на системе
	//virtual void Render(DirectX::XMMATRIX world) = 0;

	Effect* GetEffect();

protected:
	ID3D11Buffer* g_d3dVertexBuffer = nullptr;
	ID3D11Buffer* g_d3dIndexBuffer = nullptr;
	ID3D11DeviceContext* deviceContext;

	ID3D11Resource* d3dConstantBuffer;     //todo: константные буфферы должны быть в классе для Effect!

	int indicesCount;

	Texture* m_pTexture;    //todo: перенести в материал

	Effect* m_pEffect;

};