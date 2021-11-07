#pragma once

#include "Geometries/SphericalEllipticGeometry.h"
#include "WalkComponent.h"
#include "InputSystem.h"
#include "TextPrintingSystem.h"
#include "TextComponent.h"
#include "RandomSphericalGenerator.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
    double radius = 1.;

    Game& game = Game::GetInstance();
    game.InitializeEngine(L"Test game", true, false, false);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();

    {
        auto componentTypeManager = game.GetComponentTypeManager();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<InputComponent>();
        componentTypeManager->RegisterComponentType<WalkComponent>();

        componentTypeManager->RegisterComponentType<SphericalTransformComponent>();
        componentTypeManager->RegisterComponentType<SphericalCameraComponent>();

        componentTypeManager->RegisterComponentType<TextComponent>();

        //MeshComponent - registered by default

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* earthTexture = resourceManager->CreateTexture(L"earth8k.dds");

    auto renderSystem = new SphericalRenderSystem();
    renderSystem->SetRadius(radius);
    scene->AddSystem(new InputSystem());
    scene->AddSystem(renderSystem);
    scene->AddSystem(new SphericalControlSystem(0.3, 1.3));

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

    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new SphericalTransformComponent();
    auto cameraComponent = new SphericalCameraComponent();
    cameraEntity->AddComponent<SphericalTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<SphericalCameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new SphericalExpFogEffect(earthTexture, 0.1, DirectX::Colors::PowderBlue);


    auto charWalkComponent = new WalkComponent(3, 4);
    auto charInputComponent = new InputComponent();

    auto entity1 = new Entity(), entity2 = new Entity();

    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(0.1, 20, 20);
    smc->SetEffect(effect);

    /*
    cameraComponent->SetFovY(XM_PI/2 - 0.2); //эксперимент с видимостью
    int sphereCount = 6;
    for (int i = 1; i < sphereCount; i++)
    {
        auto transformComponent = new SphericalTransformComponent(0, i * XM_PI / sphereCount, 0);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);
        scene->AddEntity(entity);
    }
    for (int i = 1; i < sphereCount; i++)
    {
        auto transformComponent = new SphericalTransformComponent(0, 0, i * XM_PI / sphereCount);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);
        scene->AddEntity(entity);
    }
    */

    // --- Uniform Distribution --- //
   
    RandomSphericalGenerator generator(radius);
    int sphereCount = 20;
    for (int i = 0; i < sphereCount; i++)
    {
        auto point = generator.GeneratePoint();
        std::cout << point.x << " " << point.y << " " << point.z << " " << point.w << std::endl;
        auto transformComponent = new SphericalTransformComponent();
        transformComponent->MoveAbsolute(point.x, point.y, point.z, point.w);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);
        scene->AddEntity(entity);

        //if(пересекаются сферы с уже добавленными)
            //переген.
    }

    
    scene->AddSystem(new TextPrintingSystem());
    auto textEntity = new Entity();
    textEntity->AddComponent<TextComponent>(new TextComponent([cameraTransform, &str, &ss](double delta) {
        auto pos = cameraTransform->GetSphericalPosition();
        auto x = pos.x, y = pos.y, z = pos.z, w = pos.w;

        ss << std::fixed << std::setprecision(2);
        ss << "X: " << pos.x << std::endl;
        ss << "Y: " << pos.y << std::endl;
        ss << "Z: " << pos.z << std::endl;
        ss << "W: " << pos.w << std::endl;
        std::stringstream ss;
        return ss.str();

    }, 10, 10, Alignment::UpLeft));

    scene->AddEntity(textEntity);

    scene->AddSystem(new ActionSystem<InputComponent>(
        [effect, renderSystem](Entity* pEntity, double deltaTime) {
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();

            if (kbs.D1)
                effect->SetMode(true);
            else if (kbs.D2)
                effect->SetMode(false);

            if (kbs.I)
                renderSystem->SetRadius(renderSystem->GetRadius() + 0.1);
            else if (kbs.O)
            {
                auto radius = renderSystem->GetRadius();
                if (radius > 0.1)
                    renderSystem->SetRadius(radius -0.1);
            }
                
        }));

    return game.StartGame();
} 