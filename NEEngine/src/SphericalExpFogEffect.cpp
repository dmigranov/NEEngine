#include "pch.h"
#include "SphericalExpFogEffect.h"

#include "Game.h"

bool SphericalExpFogEffect::Initialize()
{
	//assert(g_d3dDevice);
	
	//тут выдел€етс€ пам€ть на бууферы и подобные штуки, создаютс€ шейдеры
	//input assembly тоже тут?

	return true;
}

bool SphericalExpFogEffect::Deinitialize()
{
	// пон€тно, очистка и удаление всех созданных ресурсов
}

bool SphericalExpFogEffect::SetMaterial(const Entity* pEntity)
{
	// буферы заполн€ютс€ конкретными вещами, 
	// тут же выставл€ютс€ нужные шейдеры и input assembly
	// после чего в окружающем SetMaterial,
	// возможно делаетс€ что-то еще (вызов отрисовки)

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
}
