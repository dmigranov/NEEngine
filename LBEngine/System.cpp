#include "pch.h"
#include "System.h"
#include "Game.h"
#include "ComponentTypeManager.h"

const boost::dynamic_bitset<>& System::GetComponentsMask()
{
	return m_componentsMask;
}

void System::AddEntity(Entity* pEntity)
{
	m_entities.push_back(pEntity);
}

System::System() : m_componentsMask(Game::GetInstance().GetComponentTypeManager()->GetComponentTypesCount())
{}

void System::SubscribeToComponentType(ComponentType type)
{
	std::bitset<COMPONENT_TYPE_COUNT> add = (size_t)1 << (size_t)type;
	m_componentsMask |= add;
}
