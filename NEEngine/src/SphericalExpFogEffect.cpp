#include "pch.h"
#include "SphericalExpFogEffect.h"

void SphericalExpFogEffect::Initialize()
{
	//тут выдел€етс€ пам€ть на бууферы и подобные штуки, создаютс€ шейдеры
	//input assembly тоже тут?
}

void SphericalExpFogEffect::Deinitialize()
{
	// пон€тно, очистка и удаление всех созданных ресурсов
}

void SphericalExpFogEffect::SetMaterial(const Entity* pEntity)
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
