#include "pch.h"
#include "UpdaterComponent.h"

UpdaterComponent::UpdaterComponent(std::function<void(double delta, TransformComponent* transform)> func)
{
	m_func = func;
}

void UpdaterComponent::operator()(double delta, TransformComponent* transform)
{
	m_func(delta, transform);
}
