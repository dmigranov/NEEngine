#include "pch.h"
#include "Component.h"

Component::Component()
{
}

void Component::Initialize(Entity* pEntity)
{
	m_pEntity = pEntity;
}