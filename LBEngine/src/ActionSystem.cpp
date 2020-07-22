#include "pch.h"
#include "ActionSystem.h"

ActionSystem::ActionSystem(std::function<void(Entity*, DWORD)> func, const std::list<ComponentType>& types)
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
