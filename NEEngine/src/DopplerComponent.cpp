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

void DopplerComponent::SetAlternativeTexture(bool isAlternative)
{
	m_isAlternative = isAlternative;
}

bool DopplerComponent::IsAlternativeTexture()
{
	return m_isAlternative;
}

void DopplerComponent::SetOldRadius(double oldRadius)
{
	m_oldRadius = oldRadius;
}

double DopplerComponent::GetOldRadius()
{
	return m_oldRadius;
}