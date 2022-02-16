#include "pch.h"
#include "DopplerComponent.h"

void DopplerComponent::SetSelected(bool isSelected)
{
	m_isSelected = isSelected;
}

bool DopplerComponent::IsSelected()
{
	return m_isSelected;
}
