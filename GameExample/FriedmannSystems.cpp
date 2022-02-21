#pragma once

#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CreateFriedmannSystems(System** ControlSystem, System** RadiusSystem, System** VisibilitySystem)
{
    *ControlSystem = new ActionSystem<InputComponent>([]
    (Entity* pEntity, double deltaTime) {
        });
}