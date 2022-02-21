#pragma once

#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;



FriedmannTimer* CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, System** controlSystem, System** radiusSystem, System** visibilitySystem)
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
                currentFrameTime -= deltaTime;
                SphericalDopplerEffect::SetBackwards(true);
            }
            else if (kbs.Right)
            {
                currentSimulationTime += deltaTime;
                currentFrameTime += deltaTime;
                SphericalDopplerEffect::SetBackwards(false);
            }

            if (kbs.M)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() + 100000);
            else if (kbs.N)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() - 100000);
        });
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
