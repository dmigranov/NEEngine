#include "pch.h"
#include "SphericalExpFogEffect.h"

void SphericalExpFogEffect::Initialize()
{
	//тут выдел€етс€ пам€ть на бууферы и подобные штуки, создаютс€ шейдеры
}

void SphericalExpFogEffect::Deinitialize()
{
	//пон€тно, удаление 
}

void SphericalExpFogEffect::SetMaterial(const Entity* pEntity)
{
	//буферы заполн€ютс€ конкретными вещами, после чего в окружающем SetMaterial,
	//возможно делаетс€ что-то еще (вызов отрисовки)
}
