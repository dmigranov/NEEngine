#include "pch.h"
#include "InputHandlerComponent.h"
#include "InputInfo.h"

InputHandlerComponent::InputHandlerComponent(std::function<void(Entity*, DWORD, InputInfo&)> func)
{
	m_inputHandlerFunc = func;
}

void InputHandlerComponent::operator()(Entity* pEntity, DWORD time, InputInfo &input)
{
	m_inputHandlerFunc(pEntity, time, input);
}
