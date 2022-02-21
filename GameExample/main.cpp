#pragma once

#include "main.h"

#include "InputSystem.h"
#include "TextPrintingSystem.h"
#include "TextComponent.h"
#include "DopplerComponent.h"
#include "RandomSphericalGenerator.h"
#include "SphericalMath.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
    double radius = 1.;

    Game& game = Game::GetInstance();
    game.InitializeEngine(L"Test game", true, false, true);
    game.SetBackgroundColor(DirectX::Colors::Black);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();

    {
        auto componentTypeManager = game.GetComponentTypeManager();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<InputComponent>();

        componentTypeManager->RegisterComponentType<SphericalTransformComponent>();
        componentTypeManager->RegisterComponentType<SphericalCameraComponent>();
        componentTypeManager->RegisterComponentType<SphericalRenderingComponent>();

        componentTypeManager->RegisterComponentType<TextComponent>();

        componentTypeManager->RegisterComponentType<DopplerComponent>();

        componentTypeManager->RegisterComponentType<UpdaterComponent>();

        componentTypeManager->SetTypeAdditionEnded();         //MeshComponent - registered by default
    }

    auto friedmannHwnd = CreateFriedmannWindow();

    Texture* earthTexture = resourceManager->CreateTexture(L"earth8k.dds");
    Texture* rainbowTexture1 = resourceManager->CreateTexture(L"rainbow4_rot.dds");
    Texture* rainbowTexture2 = resourceManager->CreateTexture(L"rainbow4.dds");
    Texture* greenTexture = resourceManager->CreateTexture(L"green_texture.dds");

    auto renderSystem = new SphericalRenderSystem();
    renderSystem->SetRadius(radius);
    scene->AddSystem(new InputSystem());
    scene->AddSystem(renderSystem);
    scene->AddSystem(new SphericalControlSystem(0.3, 1.3));
    scene->AddSystem(new UpdaterSystem());


    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new SphericalTransformComponent();
    auto cameraComponent = new SphericalCameraComponent();
    cameraComponent->SetFovY(XM_PI / 3);
    cameraEntity->AddComponent<SphericalTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<SphericalCameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);

    auto effect = new SphericalDopplerEffect(rainbowTexture2, 0.1, DirectX::Colors::Black);
    //auto effectEarth = new SphericalDopplerEffect(greenTexture, 0.1, DirectX::Colors::Black);
    //auto effect = new SphericalExpFogEffect(earthTexture, 0.15, DirectX::Colors::Black);

    auto pointEffect = new SphericalExpFogPointEffect(0.1, DirectX::Colors::Black);

    double objectRadius = 0.1;
    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(objectRadius, 30, 30);
    smc->SetEffect(effect);

    //auto earth_mc = SphericalMeshComponentFactory::CreateSphericalSphere(objectRadius, 30, 30);
    //earth_mc->SetEffect(effectEarth);

    auto pointComp = SphericalMeshComponentFactory::CreateSphericalPoint();
    pointComp->SetEffect(pointEffect);

    // --- Uniform Distribution --- //

    RandomSphericalGenerator generator(radius);
    int sphereCount = 100;
    auto randomPoints = new Vector4[sphereCount];
    auto entities = new Entity * [sphereCount];
    for (int i = 0; i < sphereCount; i++)
    {
    again:
        auto point = generator.GeneratePoint();

        for (int j = 0; j < i; j++)
        {
            auto otherPoint = randomPoints[j];
            auto distance = SphericalDistance(point, otherPoint, radius);

            if (distance < 2 * objectRadius)
                goto again;
        }

        randomPoints[i] = point;
        auto transformComponent = new SphericalTransformComponent();
        transformComponent->MoveAbsolute(point.x, point.y, point.z, point.w);

        auto sphericalRenderingComponent = new SphericalRenderingComponent();
        auto dopplerComponent = new DopplerComponent();
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<SphericalRenderingComponent>(sphericalRenderingComponent);
        entity->AddComponent<DopplerComponent>(dopplerComponent);
        entity->AddComponent<MeshComponent>(smc);
        //entity->AddComponent<MeshComponent>(pointComp);

        scene->AddEntity(entity);
        entities[i] = entity;
    }

    delete[] randomPoints;

    scene->AddSystem(new TextPrintingSystem());
    auto textEntity1 = new Entity();
    textEntity1->AddComponent<TextComponent>(new TextComponent([cameraTransform, renderSystem](double delta) {
        auto pos = cameraTransform->GetSphericalPosition();
        auto x = pos.x, y = pos.y, z = pos.z, w = pos.w;
        std::stringstream ss;

        ss << std::fixed << std::setprecision(2);
        ss << "X: " << pos.x << std::endl;
        ss << "Y: " << pos.y << std::endl;
        ss << "Z: " << pos.z << std::endl;
        ss << "W: " << pos.w << std::endl;
        ss << "R: " << renderSystem->GetRadius() << std::endl;

        return ss.str();

        }, 10, 10, Alignment::UpLeft, DirectX::Colors::White));

    scene->AddEntity(textEntity1);
    
    int currentSphereNumber = 1;

    auto textEntity2 = new Entity();
    textEntity2->AddComponent<TextComponent>(new TextComponent([&currentSphereNumber](double delta) {
        
        std::stringstream ss;

        ss << std::fixed << std::setprecision(2);
        if(currentSphereNumber >= 0)
            ss << "Sphere " << currentSphereNumber << std::endl;

        return ss.str();

        }, 10, 10, Alignment::DownRight, DirectX::Colors::White));

    scene->AddEntity(textEntity2);


    scene->AddSystem(new ActionSystem<InputComponent>(
        [effect, renderSystem, entities, sphereCount, cameraTransform, objectRadius,
        &currentSphereNumber, cameraComponent]
    (Entity* pEntity, double deltaTime) {

            //static double frameTime = 0;
            //static double time = 2.3;
            static auto isAnimation = true;

            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();
            auto ms = pInput->GetMouseState();

            if (kbs.D1)
                effect->SetMode(true);
            else if (kbs.D2)
                effect->SetMode(false);

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
            {
                effect->SetVelocityCoefficient(effect->GetVelocityCoefficient() + 100000);
            }
            else if (kbs.N)
            {
                effect->SetVelocityCoefficient(effect->GetVelocityCoefficient() - 100000);
            }

            double mu = currentSimulationTime / 3.;
            double radius = 2 * (1 - cos(mu));

            if (isAnimation)
            {
                if (radius > 0.5)
                {
                    currentSimulationTime += deltaTime;
                    currentFrameTime += deltaTime;
                    SphericalDopplerEffect::SetBackwards(false);
                    mu = currentSimulationTime / 3.;                 //если закомментировать эти две строчки с обновлением mu и radius, то есть мерцание
                    radius = 2 * (1 - cos(mu));     //то есть, если эти строчки закомментированы, то мы считаем радиус для предыдущего фрейма
                                                    //и из этого как-то вытекает мерцание - todo
                }
                else
                    isAnimation = false;
            }

            auto cameraPos = cameraTransform->GetSphericalPosition();
            renderSystem->SetRadius(radius);

            for (int i = 0; i < sphereCount; i++)
            {
                Entity* sphere = entities[i];
                auto pTransform = sphere->GetComponent<SphericalTransformComponent>();
                auto pos = pTransform->GetSphericalPosition();
                auto renderingComponent = sphere->GetComponent<SphericalRenderingComponent>();
                auto visibility = renderingComponent->GetSphericalVisibility();

                auto dist = SphericalDistance(pos / radius, cameraPos / radius, 1.);
                
                if (mu < dist)
                    renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_NONE);
                else if (mu >= dist && mu <= (2 * XM_PI - dist))
                    renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_FRONT);
                else //mu > (2 * XM_PI - dist)
                    renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_ALL);
            }

            if (currentFrameTime >= 0.1 || currentFrameTime <= -0.1)
            {
                UpdateFriedmannWindow(mu);
                currentFrameTime = 0;
            }
            
            {
                const auto& view = cameraTransform->GetView();  

                //radius of spheres in the Euclidean space, after projection
                auto w_sphere = radius - 2 * radius * pow(sin(objectRadius / radius / 2), 2);
                auto r_sphere = sqrt(radius * radius - w_sphere * w_sphere);
                auto r_projected = r_sphere / w_sphere;
                auto r_projected_sq = r_projected * r_projected;

                // todo: идея: при проецировании использовать вместо view - произведение view на матрицу, 
                // передвигающую её (прямо - просто движение по z) к объекту
                // это решит проблему нулевого w 

                // todo: идея: также цикл по всем объектам (можно отбросить все с отрицательным z
                // после применения view, а может, не надо - копии тоже можно выбирать)
                // осуществляем проецирование, и проверяем близость центра до координат выбранной 
                // курсором точки. Единственная проблема - подсчитать нужный радиус проецирования

                // position - always (0, 0, 0)
                // direction - always (0, 0, 1)
                Vector3 rayStart(0.f, 0.f, 0.f);
                Vector3 direction(0.f, 0.f, 1.f);

                float minDist = 100000.;
                int minIndex = -1;

                for (int i = 0; i < sphereCount; i++)
                {
                    Entity* sphere = entities[i];
                    auto pTransform = sphere->GetComponent<SphericalTransformComponent>();
                    auto sphericalPosition = pTransform->GetSphericalPosition();

                    double t = RayTraceSpherePos(sphericalPosition, rayStart, direction, view, r_projected_sq);
                    if (t < 0)
                    {
                        continue;
                        //t = RayTraceSphereNeg(sphericalPosition, rayStart, direction, view, r_projected_sq);
                        //if (t < 0)
                        //    continue; //todo: чтобы во всех четвертях работало
                    }

                    if (t < minDist) {
                        minDist = t;
                        minIndex = i;
                    }
                    
                }

                currentSphereNumber = minIndex;
                if (minIndex >= 0)
                {
                    auto selectedEntity = entities[currentSphereNumber];
                    auto dopplerComponent = selectedEntity->GetComponent <DopplerComponent>();
                    if (ms.rightButton)
                        dopplerComponent->SetSelected(true);
                    else if (kbs.Space)
                        dopplerComponent->SetSelected(false);
                }
            }
        }));

    System* controlSystem = nullptr;
    //System* controlSystem = nullptr;

    CreateFriedmannSystems(effect, &controlSystem, nullptr, nullptr);

    return game.StartGame();
}







/*
    scene->AddSystem(new ActionSystem<InputComponent, SphericalTransformComponent, WalkComponent>(
        [](Entity* pEntity, double deltaTime) {
            auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();
            auto ms = pInput->GetMouseState();
            auto pWalk = pEntity->GetComponent<WalkComponent>();


            Vector3 up(0, deltaTime * pWalk->m_movementGain, 0);
            Vector3 right(deltaTime * pWalk->m_movementGain, 0, 0);
            Vector3 fwd(0, 0, deltaTime * pWalk->m_movementGain);


            if (kbs.R)
                pTransform->Move(up);
            if (kbs.F)
                pTransform->Move(-up);

            if (kbs.T)
                pTransform->Rotate(deltaTime, 0, 0);
            if (kbs.G)
                pTransform->Rotate(0, deltaTime, 0);
            if (kbs.B)
                pTransform->Rotate(0, 0, deltaTime);
        }));
        */