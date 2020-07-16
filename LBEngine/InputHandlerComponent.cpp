#include "pch.h"
#include "InputHandlerComponent.h"
#include "InputInfo.h"

InputHandlerComponent::InputHandlerComponent(std::function<void(Entity*, InputInfo)> func)
{
	m_inputHandlerFunc = func;
}

void InputHandlerComponent::operator()(Entity* pEntity, InputInfo input)
{
	m_inputHandlerFunc(pEntity, input);
}
