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
                //todo: вопрос: остаетс€ ли выделение после (сейчас - нет)?
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

    double length = 0.1;
    double maxRadius = 4.;
    m_pSound = new DynamicSound([this, length, maxRadius](int16_t* data, int sampleRate, int frequency) {
        // sampleRate - количество сэмплов
        
        static double timeForCurrentObject = 0.0; //а может сразу в сэмплах измер€ть?
        static unsigned long sampleCountForCurrentObject = 0; 

        static double minKnockFrequency = 0.01, maxKnockFrequency = 10.;

        if (m_hasObjectChanged)  //todo: radius changed!
        {
            timeForCurrentObject = 0.;
            sampleCountForCurrentObject = 0;
            m_hasObjectChanged = false;
        }

        auto radius = SphericalEffect::GetRadius();

        const double timeStep = length / double(sampleRate); //length instead of 1?
        const double freq = double(frequency);

        int16_t* ptr = data;
        double time = 0.0;
        
        int playSampleCount = 100; //delta

        double distanceNormalized = 1 - m_currentChi * radius / XM_2PI / maxRadius;
        //double distanceNormalized = 1 - m_currentChi / XM_2PI;
        double knockFrequency = minKnockFrequency + distanceNormalized * (maxKnockFrequency - minKnockFrequency);
        std::cout << knockFrequency << std::endl;
        double mustBePlayedEverySeconds = 1. / knockFrequency;

        unsigned int mustBePlayedEverySamples = (double)sampleRate / length * mustBePlayedEverySeconds; //вместо 44100 * mustBePlayedEverySeconds; так больше операций, но не зав€заны на 44100

        int numberSamplesPlayed = 0;
        for (int j = 0; j < sampleRate; ++j, ++ptr)
        {
            double angle = (2.0 * XM_PI * freq) * time;
            //if (j==0 || j == sampleRate - 1)
            //    std::cout << time << " " << sin(angle) << std::endl;

            double factor = 0.;
            if(m_currentChi > 0 &&
                            ((sampleCountForCurrentObject + j) % mustBePlayedEverySamples < playSampleCount))
            {
                //double angle = (XM_2PI * freq) * timeStep * ((sampleCountForCurrentObject + j) % mustBePlayedEverySamples);
                //todo: сделать синусоиду, чтобы укоадывалась во все звучащие сэмплы
                factor = sin(angle); //from -1 to 1
                numberSamplesPlayed++;
            }
            // PCM 16 bit: -32 767 Е 32 767 
            *ptr = int16_t(32768 * factor);
            time += timeStep;
        }

        //std::cout << sampleCountForCurrentObject << " " << mustBePlayedEverySamples << " " << (sampleCountForCurrentObject + sampleRate) % mustBePlayedEverySamples << std::endl;
        timeForCurrentObject += length;
        sampleCountForCurrentObject += sampleRate;
        //sampleCountForCurrentObject = (sampleCountForCurrentObject + sampleRate) % mustBePlayedEverySamples;
    }, length);

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

        //! проблема в том, что тут успевает стать false!
        if (m_currentEntity != pSelectedEntity)
            m_hasObjectChanged = true;
        //else
        //    m_hasObjectChanged = false;

        m_currentEntity = pSelectedEntity;

        /*
        //pitch = -1.99 * (chi / XM_2PI - 0.5); //old, based on chi
        
        auto maxRadius = 4.; //! has to be changed if the radius formula is changed
        pitch = -1.99 *  (chi * radius / maxRadius / XM_2PI - 0.5); // alternative formula
        //или рассто€ние надо считать по-другому, не как chi * radius?

        m_pSound->SetVolume(1.);
        m_pSound->SetPitch(pitch);
        */

        //m_pSound->SetPan(-1);
    }
    else
    {
        m_currentChi = -1;
        m_currentEntity = nullptr;
        //m_pSound->SetVolume(0.);
        //m_pSound->SetPitch(0.f);
    }
}


// Ќа вс€кий случай: код без изменений (одна система на всЄ) - по состо€нию на начало 21.02.2022

/*
m_pSound = new DynamicSound([this, length](int16_t* data, int sampleRate, int frequency) {
        static double currentTime = 0.0; //а может сразу в сэмплах измер€ть?

        const double timeStep = 1.0 / double(sampleRate);
        const double freq = double(frequency);

        int16_t* ptr = data;
        double time = 0.0;


        // дл€ дальнейшего ”ћ≈Ќ№Ў≈Ќ»я частоты:
        // прибавл€ть и % на currentTickMax
        // звук - только когда currentTick = 0!
        static unsigned int currentTick = 0;
        static unsigned int currentTickMax = 1;
        if (m_hasObjectChanged)
        {
            currentTick = 0;
        }

        size_t sampleCount = m_pSound->GetSampleCount();

        int repetitionStep = 0;
        int soundSampleCount = 50;
        if (m_currentChi > 0)
        {
            if (m_currentChi < XM_PI)
            {
                int repetitionCount = (10 - (int)(m_currentChi / XM_PI * 10)); //было 2PI
                repetitionStep = sampleCount / repetitionCount;
                currentTick = 0;
            }
            else
            {
                repetitionStep = sampleCount;
                currentTickMax = ((m_currentChi - XM_PI) / XM_PI * 10); //проверить, вылетает!
            }
        }

        auto radius = SphericalEffect::GetRadius();

        for (int j = 0; j < sampleCount; ++j, ++ptr)
        {
            double angle = (2.0 * XM_PI * freq) * time;
            //double factor = 0.5 * (sin(angle) + 1.0); //from 0 to 1
            double factor = (currentTick == 0 && repetitionStep > 0 && j % repetitionStep < soundSampleCount)
                ? sin(angle)
                : 0; //from -1 to 1

            // PCM 16 bit: -32 767 Е 32 767
            *ptr = int16_t(32768 * factor);
            time += timeStep;
        }
        //todo: вылетает!

        currentTick = (currentTick + 1) % currentTickMax;
        currentTime += length;
    }, length);
*/