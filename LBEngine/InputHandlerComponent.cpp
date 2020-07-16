#include "pch.h"
#include "InputHandlerComponent.h"

InputHandlerComponent::InputHandlerComponent(std::function<void(Entity*, InputInfo)> func)
{
	m_inputHandlerFunc = func;
}
