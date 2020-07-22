#include "pch.h"
#include "ActionSystem.h"

ActionSystem::ActionSystem(const std::list<ComponentType>& types, std::function<void(Entity*, DWORD)> func)
{
	for(auto type : types)
		SubscribeToComponentType(type);
	m_executeFunc = func;
}

void ActionSystem::Execute(DWORD deltaTime)
{
	for (auto pEntity : m_entities)
	{
		m_executeFunc(pEntity, deltaTime);
	}
}
