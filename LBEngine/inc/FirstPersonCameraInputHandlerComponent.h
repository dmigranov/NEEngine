#pragma once
#include "InputHandlerComponent.h"
class FirstPersonCameraInputHandlerComponent :
    public InputHandlerComponent
{
public:
    //todo: добавить параметры...
    FirstPersonCameraInputHandlerComponent();
private:
    double m_movementGain = 0.003;
    double m_rotationGain = 0.004;
};