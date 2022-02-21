#pragma once

#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CreateFriedmannSystems(System** ControlSystem, System** RadiusSystem, System** VisibilitySystem)
{
    *ControlSystem = new ActionSystem<InputComponent>([]
    (Entity* pEntity, double deltaTime) {
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();
            auto ms = pInput->GetMouseState();

            if (kbs.D1)
                effect->SetMode(true);
            else if (kbs.D2)
                effect->SetMode(false);
        });
}