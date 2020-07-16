#include "pch.h"
#include "System.h"

void System::SubscribeToComponentType(ComponentType type)
{
	std::bitset<COMPONENT_TYPE_COUNT> add = 1 << (size_t)type;
	m_componentsMask |= add;
}
