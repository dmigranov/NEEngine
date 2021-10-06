#include "pch.h"
#include "UpdaterComponent.h"


UpdaterComponent::UpdaterComponent(std::function<void(double delta, Entity* pEntity)> func)
{
	m_func = func;
}

void UpdaterComponent::operator()(double delta, Entity* pEntity)
{
	m_func(delta, pEntity);
}
