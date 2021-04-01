#include "pch.h"
#include "SphericalExpFogEffect.h"

//потом вернуть, а пока множ. определение
//#include "VertexShader.h" // generated from BasicVertexShader.hlsl
//#include "PixelShader.h" // generated from BasicPixelShader.hlsl

#include "Game.h"

bool SphericalExpFogEffect::Initialize()
{
	auto& game = Game::GetInstance();
	//тут выдел€етс€ пам€ть на бууферы и подобные штуки, создаютс€ шейдеры
	
	//shaders
	g_d3dVertexShader = game.CreateVertexShaderFromBytecode(g_vs, sizeof(g_vs));
	g_d3dPixelShader = game.CreatePixelShaderFromBytecode(g_ps, sizeof(g_ps));

	//input assembly тоже тут?
	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, offsetof(VertexData, Position), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	g_d3dInputLayout = game.CreateInputLayout(vertexLayoutDesc, _countof(vertexLayoutDesc), g_vs, sizeof(g_vs));

	return true;
}

bool SphericalExpFogEffect::Deinitialize()
{
	// пон€тно, очистка и удаление всех созданных ресурсов
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
