#pragma once

#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



FriedmannTimer* CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, 
    System** controlSystem, System** radiusVisibilitySystem)
{
    auto timer = new FriedmannTimer(2.3, 0.1);

    *controlSystem = new ActionSystem<InputComponent>([sphericalEffect, timer]
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
                timer->AddDelta(-deltaTime);
                SphericalDopplerEffect::SetBackwards(true);
            }
            else if (kbs.Right)
            {
                timer->AddDelta(deltaTime);
                SphericalDopplerEffect::SetBackwards(false);
            }

            if (kbs.M)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() + 100000);
            else if (kbs.N)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() - 100000);
        });


    *radiusVisibilitySystem = new ActionSystem<SphericalTransformComponent, SphericalRenderingComponent>([sphericalEffect, timer]
    (Entity* pEntity, double deltaTime) {
            auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
            auto pos = pTransform->GetSphericalPosition();
            auto renderingComponent = pEntity->GetComponent<SphericalRenderingComponent>();
            auto visibility = renderingComponent->GetSphericalVisibility();


        });

    return timer;
}

FriedmannTimer::FriedmannTimer(double initialSimulationTime, double frameTimeLimit)
{
    m_currentSimulationTime = initialSimulationTime;
    m_frameTimeLimit = frameTimeLimit;
}

void FriedmannTimer::AddDelta(double deltaTime)
{
    m_currentSimulationTime += deltaTime;
    m_currentFrameTime += deltaTime;
}

bool FriedmannTimer::IsTimeToRepaint()
{
    if (m_currentFrameTime >= m_frameTimeLimit || m_currentFrameTime <= -m_frameTimeLimit)
    {
        m_currentFrameTime = 0;
        return true;  
    }
    return false;
}

double FriedmannTimer::GetSimulationTime()
{
    return m_currentSimulationTime;
}

double FriedmannTimer::GetFrameTime()
{
    return m_currentFrameTime;
}

void FriedmannTimer::SetFrameTime(double newTime)
{
    m_currentFrameTime = newTime;
}
