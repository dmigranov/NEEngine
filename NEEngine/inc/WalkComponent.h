#pragma once
#include "Component.h"
class WalkComponent :
    public Component
{
public:
    WalkComponent(double movementGain, double rotationGain);

    double m_movementGain;
    double m_rotationGain;
};