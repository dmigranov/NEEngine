#include "pch.h"
#include "InputHandlerComponent.h"
#include "InputComponent.h"

InputHandlerComponent::InputHandlerComponent(std::function<void(Entity*, DWORD, InputComponent&)> func)
{
	m_inputHandlerFunc = func;
}

void InputHandlerComponent::operator()(Entity* pEntity, DWORD time, InputComponent &input)
{
	m_inputHandlerFunc(pEntity, time, input);
}
