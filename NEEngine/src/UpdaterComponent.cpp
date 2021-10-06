#include "pch.h"
#include "UpdaterComponent.h"

UpdaterComponent::UpdaterComponent(std::function<void(double delta, TransformComponent* pTransform)> func)
{
	m_func = func;
}

void UpdaterComponent::operator()(double delta, TransformComponent* pTransform)
{
	m_func(delta, pTransform);
}
