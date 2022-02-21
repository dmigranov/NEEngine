#pragma once

#include "main.h"

#include "SphericalMath.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;



FriedmannTimer* CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, SphericalTransformComponent* cameraTransform,
    System** controlSystem, System** visibilitySystem, System** radiusUpdateSystem)
{
    auto timer = new FriedmannTimer(2.3, 0.1, 1./3.);

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


    *visibilitySystem = new ActionSystem<SphericalTransformComponent, SphericalRenderingComponent>([sphericalEffect, cameraTransform, timer]
    (Entity* pEntity, double deltaTime) {
            auto cameraPos = cameraTransform->GetSphericalPosition();

            auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
            auto pos = pTransform->GetSphericalPosition();
            auto renderingComponent = pEntity->GetComponent<SphericalRenderingComponent>();
            auto visibility = renderingComponent->GetSphericalVisibility();

            auto radius = SphericalEffect::GetRadius();
            auto dist = SphericalDistance(pos / radius, cameraPos / radius, 1.);
            auto mu = timer->GetMu();

            if (mu < dist)
                renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_NONE);
            else if (mu >= dist && mu <= (XM_2PI - dist))
                renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_FRONT);
            else //mu > (2 * XM_PI - dist)
                renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_ALL);
        });

    *radiusUpdateSystem = new RadiusUpdateSystem();

    return timer;
}

FriedmannTimer::FriedmannTimer(double initialSimulationTime, double frameTimeLimit, double muCoeff)
{
    m_currentSimulationTime = initialSimulationTime;
    m_frameTimeLimit = frameTimeLimit;
    m_muCoeff = muCoeff;
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

double FriedmannTimer::GetMu()
{
    return m_currentSimulationTime * m_muCoeff;
}

double FriedmannTimer::GetFrameTime()
{
    return m_currentFrameTime;
}

void FriedmannTimer::SetFrameTime(double newTime)
{
    m_currentFrameTime = newTime;
}

RadiusUpdateSystem::RadiusUpdateSystem()
{

}

void RadiusUpdateSystem::Execute(double deltaTime)
{

}

// �� ������ ������: ��� ��� ��������� (���� ������� �� ��) - �� ��������� �� ������ 21.02.2022