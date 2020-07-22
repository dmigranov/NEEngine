#include "pch.h"
#include "WalkComponent.h"
#include "..\inc\WalkComponent.h"

WalkComponent::WalkComponent(double movementGain, double rotationGain)
{
	m_movementGain = movementGain;
	m_rotationGain = rotationGain;
}
