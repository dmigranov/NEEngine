#pragma once
#include "ActionSystem.h"

#include "Entity.h"
#include "InputComponent.h"
#include "HyperbolicTransformComponent.h"
#include "HyperbolicCameraComponent.h"

class HyperbolicControlSystem :
    public ActionSystem<InputComponent, HyperbolicTransformComponent, HyperbolicCameraComponent>
{
};

