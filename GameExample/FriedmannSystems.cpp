#pragma once

#include "main.h"

#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


FriedmannTimer* CreateFriedmannSystems(SphericalDopplerEffect* sphericalEffect, 
    SphericalTransformComponent* cameraTransform, SphericalRenderSystem* renderSystem, InputComponent* inputComponent, double initialObjectRadius, Sound * pSound,
    System** controlSystem, System** visibilitySystem, System** radiusUpdateSystem, 
    System** animationSystem, SelectionSystem** selectionSystem, System** soundSystem)
{
    double initialMuCoeff = 1. / 3.;
    double initialSimulationTime = 8. / (9. * initialMuCoeff);

    double frameUpdateTimeLimit = 0.1;

    auto timer = new FriedmannTimer(initialSimulationTime, frameUpdateTimeLimit, initialMuCoeff);
    double initialSimulationMu = timer->GetMu();

    *selectionSystem = new SelectionSystem(inputComponent, timer, initialObjectRadius);

    *controlSystem = new ActionSystem<InputComponent>([sphericalEffect, timer, selectionSystem]
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
            }
            else if (kbs.Right)
            {
                timer->AddDelta(deltaTime);
            }

            double muCoeffDelta = 0.01; 
            if (kbs.Up)
            {
                timer->SetMuCoeff(timer->GetMuCoeff() + muCoeffDelta);
            }
            else if (kbs.Down)
            {
                auto muCoeff = timer->GetMuCoeff();
                if (muCoeff >= muCoeffDelta)
                    timer->SetMuCoeff(muCoeff - muCoeffDelta);
            }

            if (kbs.M)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() + 100000);
            else if (kbs.N)
                sphericalEffect->SetVelocityCoefficient(sphericalEffect->GetVelocityCoefficient() - 100000);

            auto entities = (*selectionSystem)->GetEntities();
            auto objectRadius = 0.1;
            auto radius = SphericalEffect::GetRadius();

            auto selectedEntity = (*selectionSystem)->GetSelectedEntity();
            static bool oldPressedSelectButton = false;
            if (selectedEntity != nullptr)
            {
                auto dopplerComponent = selectedEntity->GetComponent <DopplerComponent>();
                if (ms.rightButton)
                {
                    if (!oldPressedSelectButton)
                    {
                        dopplerComponent->SetSelected(!dopplerComponent->IsSelected());
                    }
                    oldPressedSelectButton = true;
                }
                else
                    oldPressedSelectButton = false;
            }


            static bool oldPressedInvertButton = false;
            if (kbs.I)
            {
                if (!oldPressedInvertButton)
                    for (auto pEntity : entities)
                    {
                        auto dopplerComponent = pEntity->GetComponent <DopplerComponent>();
                        dopplerComponent->SetSelected(!dopplerComponent->IsSelected());
                    }
                oldPressedInvertButton = true;
            }
            else
                oldPressedInvertButton = false;


            if (kbs.V)
            {
                //todo: вопрос: остается ли выделение после (сейчас - нет)?
                for (auto pEntity : entities)
                {
                    auto dopplerComponent = pEntity->GetComponent <DopplerComponent>();
                    if (dopplerComponent->IsSelected())
                    {
                        pEntity->SetVisible(false);
                        dopplerComponent->SetSelected(false);
                    }
                } 
            }


            static bool oldPressedTextureButton = false;
            if (kbs.T)
            {
                if (!oldPressedTextureButton)
                    for (auto pEntity : entities)
                    {
                        auto dopplerComp = pEntity->GetComponent<DopplerComponent>();
                        if (dopplerComp->IsSelected())
                        {
                            dopplerComp->SetAlternativeTexture(!dopplerComp->IsAlternativeTexture());
                        }
                    }
                oldPressedTextureButton = true;
            }
            else
                oldPressedTextureButton = false;


            if (kbs.R) //revert
                for (auto pEntity : entities)
                {
                    auto dopplerComponent = pEntity->GetComponent <DopplerComponent>();
                    dopplerComponent->SetSelected(false);
                    dopplerComponent->SetAlternativeTexture(false);
                    pEntity->SetVisible(true);
                }
        });

    *visibilitySystem = new ActionSystem<SphericalTransformComponent, SphericalRenderingComponent>([sphericalEffect, cameraTransform, timer]
    (Entity* pEntity, double deltaTime) {
            auto cameraPos = cameraTransform->GetSphericalPosition();

            auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
            auto pos = pTransform->GetSphericalPosition();
            auto renderingComponent = pEntity->GetComponent<SphericalRenderingComponent>();
            auto visibility = renderingComponent->GetSphericalVisibility();

            auto radius = SphericalEffect::GetRadius();
            auto dist = SphericalDistance(pos / radius, cameraPos / radius, 1.); // dist is Chi 
            auto mu = timer->GetMu();

            if (mu < dist)
                renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_NONE);
            else
            {
                if (mu >= dist && mu <= (XM_2PI - dist))
                {
                    renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_FRONT);
                }
                else //mu > (2 * XM_PI - dist)
                {
                    renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_ALL);
                }
            }
        });

    *radiusUpdateSystem = new RadiusUpdateSystem(timer, renderSystem, cameraTransform);
    double initialRadius = ((RadiusUpdateSystem*)(*radiusUpdateSystem))->RadiusFunction(initialSimulationMu);

    *animationSystem = new ActionSystem<InputComponent>(
        [timer, initialRadius] (Entity* pEntity, double deltaTime) {
            static auto isAnimation = true;

            double radius = SphericalEffect::GetRadius();
            if (isAnimation)
            {
                if (radius >= initialRadius)
                {
                    timer->AddDelta(deltaTime);
                }
                else
                    isAnimation = false;
            }
        });

    *soundSystem = new SoundSystem(pSound, *selectionSystem, cameraTransform);

    return timer;
}

FriedmannTimer::FriedmannTimer(double initialSimulationTime, double frameUpdateTimeLimit, double muCoeff)
{
    m_currentSimulationTime = initialSimulationTime;
    m_mu = muCoeff * m_currentSimulationTime;

    m_frameUpdateTimeLimit = frameUpdateTimeLimit;
    m_muCoeff = muCoeff;
}

void FriedmannTimer::AddDelta(double deltaTime)
{
    m_currentSimulationTime += deltaTime;
    m_currentFrameTime += deltaTime;
    m_mu += m_muCoeff * deltaTime;
}

bool FriedmannTimer::IsTimeToRepaint()
{
    if (m_currentFrameTime >= m_frameUpdateTimeLimit || m_currentFrameTime <= -m_frameUpdateTimeLimit)
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
    return m_mu;
}

double FriedmannTimer::GetFrameTime()
{
    return m_currentFrameTime;
}

void FriedmannTimer::SetMuCoeff(double muCoeff)
{
    m_muCoeff = muCoeff;
}

double FriedmannTimer::GetMuCoeff()
{
    return m_muCoeff;
}

void FriedmannTimer::SetFrameTime(double newTime)
{
    m_currentFrameTime = newTime;
}

RadiusUpdateSystem::RadiusUpdateSystem(FriedmannTimer * timer, SphericalRenderSystem* renderSystem, SphericalTransformComponent* cameraTransform)
{
    SubscribeToComponentType<SphericalTransformComponent>();
    SubscribeToComponentType<DopplerComponent>();

    m_timer = timer;
    m_renderSystem = renderSystem;
    m_cameraTransform = cameraTransform;
    m_radiusFunction = [](double mu) { return 2 * (1 - cos(mu)); };
}

void RadiusUpdateSystem::Execute(double deltaTime)
{
    double mu = m_timer->GetMu();
    //double radius = 2 * (1 - cos(mu));
    double radius = m_radiusFunction(mu);

    m_renderSystem->SetRadius(radius);
    SphericalDopplerEffect::SetMu(mu);

    if (m_timer->IsTimeToRepaint())
    {
        UpdateFriedmannWindow(mu);
    }

}

double RadiusUpdateSystem::RadiusFunction(double mu)
{
    return m_radiusFunction(mu);
}

SoundSystem::SoundSystem(Sound* pSound, SelectionSystem* pSelectionSystem, SphericalTransformComponent* pCameraTransform)
{
    m_pSoundOld = pSound;

    m_pSound = new DynamicSound([this](int16_t* data, int sampleRate, int frequency) {
        const double timeStep = 1.0 / double(sampleRate);
        const double freq = double(frequency);

        int16_t* ptr = data;
        double time = 0.0;

        size_t sampleCount = m_pSound->GetSampleCount(); 

        int repetitionStep = 0;
        int soundSampleCount = 50;
        if (m_currentChi > 0)
        {
            int repetitionCount = (int)(11 - m_currentChi / XM_2PI * 10);
            repetitionStep = sampleCount / repetitionCount;
        }

        for (int j = 0; j < sampleCount; ++j, ++ptr)
        {

            double angle = (2.0 * XM_PI * freq) * time;
            //double factor = 0.5 * (sin(angle) + 1.0); //from 0 to 1
            //double factor = (double)(sampleCount/2 - j) / sampleCount * 2 * (j > sampleCount / 2) ? 0 : sin(angle); //from -1 to 1            //double factor = (double)(sampleCount/2 - j) / sampleCount * 2 * (j > sampleCount / 2) ? 0 : sin(angle); //from -1 to 1
            double factor = (repetitionStep > 0 && j % repetitionStep < soundSampleCount) ? sin(angle) : 0; //from -1 to 1

            // PCM: 16 bit
            // -32 767 … 32 767 

            *ptr = int16_t(32768 * factor);
            time += timeStep;
        }
        }, 0.5);
    m_pSound->Play();

    m_pSelectionSystem = pSelectionSystem;
    m_pCameraTransform = pCameraTransform;
}

void SoundSystem::Execute(double deltaTime)
{
    auto pSelectedEntity = m_pSelectionSystem->GetSelectedEntity();
    if (pSelectedEntity != nullptr)
    {
        float pitch;
        const auto& view = m_pCameraTransform->GetView();

        auto pSphTransform = pSelectedEntity->GetComponent<SphericalTransformComponent>();
        auto sphPosWorld = pSphTransform->GetSphericalPosition();
        auto sphPosView = Vector4::Transform(sphPosWorld, view); //pos_view

        auto radius = SphericalEffect::GetRadius();
        double chi = acos(sphPosView.w / radius);

        if (sphPosView.z < 0)
            chi = XM_2PI - chi;

        m_currentChi = chi;
        /*
        //pitch = -1.99 * (chi / XM_2PI - 0.5); //old, based on chi
        
        auto maxRadius = 4.; //! has to be changed if the radius formula is changed
        pitch = -1.99 *  (chi * radius / maxRadius / XM_2PI - 0.5); // alternative formula
        //или расстояние надо считать по-другому, не как chi * radius?

        m_pSound->SetVolume(1.);
        m_pSound->SetPitch(pitch);
        */
    }
    else
    {
        m_currentChi = -1;
        //m_pSound->SetVolume(0.);
        //m_pSound->SetPitch(0.f);
    }
}


// На всякий случай: код без изменений (одна система на всё) - по состоянию на начало 21.02.2022