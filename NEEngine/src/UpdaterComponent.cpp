#include "pch.h"
#include "UpdaterComponent.h"

UpdaterComponent::UpdaterComponent(std::function<void(double delta)> func)
{
	m_func = func;
}

void UpdaterComponent::operator()(double delta)
{
	m_func(delta);
}
