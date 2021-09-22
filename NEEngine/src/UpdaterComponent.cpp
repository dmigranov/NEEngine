#include "pch.h"
#include "UpdaterComponent.h"

UpdaterComponent::UpdaterComponent(std::function<void(float delta)> func)
{
	m_func = func;
}
