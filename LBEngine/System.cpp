#include "pch.h"
#include "System.h"

const std::bitset<COMPONENT_TYPE_COUNT>& System::GetComponentsMask()
{
	return m_componentsMask;
}

void System::AddEntity(Entity* pEntity)
{
}

void System::SubscribeToComponentType(ComponentType type)
{
	std::bitset<COMPONENT_TYPE_COUNT> add = (size_t)1 << (size_t)type;
	m_componentsMask |= add;
}
