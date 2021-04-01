#include "pch.h"
#include "SphericalExpFogEffect.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


//потом вернуть, а пока множ. определение
//#include "VertexShader.h" // generated from BasicVertexShader.hlsl
//#include "PixelShader.h" // generated from BasicPixelShader.hlsl

#include "Game.h"

bool SphericalExpFogEffect::Initialize()
{
	auto& game = Game::GetInstance();

	//shaders
	g_d3dVertexShader = game.CreateVertexShaderFromBytecode(g_vs, sizeof(g_vs));
	g_d3dPixelShader = game.CreatePixelShaderFromBytecode(g_ps, sizeof(g_ps));

	//input assembly тоже тут:
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexData, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	g_d3dInputLayout = game.CreateInputLayout(vertexLayoutDesc, _countof(vertexLayoutDesc), g_vs, sizeof(g_vs));


	//буферы (в тч текстурные):
	D3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	//we will update the contents of buffers using the ID3D11DeviceContext::UpdateSubresource method and this method expects constant buffers to be initialized with D3D11_USAGE_DEFAULT usage flag and buffers that are created with the D3D11_USAGE_DEFAULT flag must have their CPUAccessFlags set to 0.
	//todo: может, лучше сделать Dynamic, ведь некоторые часто обновл€ютс€?!! ѕќƒ”ћј“№

	constantBufferDesc.ByteWidth = sizeof(Matrix);


	return true;
}

bool SphericalExpFogEffect::Deinitialize()
{
	// пон€тно, очистка и удаление всех созданных ресурсов

	//SafeRelease(g_d3dVSConstantBuffers[CB_Application]);
	//SafeRelease(g_d3dVSConstantBuffers[CB_Frame]);
	//SafeRelease(g_d3dVSConstantBuffers[CB_Object]);
	//SafeRelease(g_d3dPSConstantBuffer);

	SafeRelease(g_d3dInputLayout);

	SafeRelease(g_d3dVertexShader);
	SafeRelease(g_d3dPixelShader);

	return true;
}

bool SphericalExpFogEffect::SetMaterial(const Entity* pEntity)
{
	// буферы заполн€ютс€ конкретными вещами, 
	// тут же выставл€ютс€ нужные шейдеры и input assembly
	// после чего в окружающем SetMaterial,
	// возможно делаетс€ что-то еще (вызов отрисовки)


	game.SetVertexShader(g_d3dVertexShader);
	game.SetPixelShader(g_d3dPixelShader);


	/*
	SetMaterialBegin();
	{
		SetVertexShaderBegin();
		SetVertexShaderMatrix4x4("matrixWorldViewProjT", matWorldViewProjT);
		SetVertexShaderVector4("constColor", Vector4(1, 1, 1, 1));
		SetVertexShaderEnd();

		SetPixelShaderBegin();
		SetPixelShaderTexture2d("texture1", m_pTexture1);
		SetPixelShaderEnd();
	}
	SetMaterialEnd();
	*/

	return true;
}

SphericalExpFogEffect::~SphericalExpFogEffect()
{
	Deinitialize();
}
