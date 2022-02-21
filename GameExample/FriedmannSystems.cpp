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

            if (kbs.Left)
            {
                currentSimulationTime -= deltaTime;
                // frameTime -= deltaTime;
                SphericalDopplerEffect::SetBackwards(true);
            }
            else if (kbs.Right)
            {
                currentSimulationTime += deltaTime;
                //frameTime += deltaTime;
                SphericalDopplerEffect::SetBackwards(false);
            }

            if (kbs.M)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() + 100000);
            else if (kbs.N)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() - 100000);
        });
}