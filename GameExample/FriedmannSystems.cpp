#pragma once

#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, System** controlSystem, System** radiusSystem, System** visibilitySystem)
{
    *controlSystem = new ActionSystem<InputComponent>([sphericalEffect]
    (Entity* pEntity, double deltaTime) {
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();
            auto ms = pInput->GetMouseState();

            if (kbs.D1)
                sphericalEffect->SetMode(true);
            else if (kbs.D2)
                sphericalEffect->SetMode(false);
        });
}