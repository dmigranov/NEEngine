#pragma once
#include "ActionSystem.h"

class InputComponent;
class ToricTransformComponent;
class CameraComponent;

class ToricControlSystem 
    : public ActionSystem<InputComponent, ToricTransformComponent, CameraComponent>
{
public:
    ToricControlSystem(double movementSpeed, double rotationSpeed);
};

