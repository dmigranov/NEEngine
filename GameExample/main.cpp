#pragma once

#include "Geometries/SphericalEllipticGeometry.h"
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
    game.InitializeEngine(1280, 720, L"Spherical & Elliptic Spaces", true, false, false);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();

    {
        auto componentTypeManager = game.GetComponentTypeManager();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<InputComponent>();

        componentTypeManager->RegisterComponentType<SphericalTransformComponent>();
        componentTypeManager->RegisterComponentType<SphericalCameraComponent>();

        componentTypeManager->RegisterComponentType<TextComponent>();

        //MeshComponent - registered by default

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* earthTexture = new Texture(L"earth8k.dds");

    auto renderSystem = new SphericalRenderSystem();
    renderSystem->SetRadius(radius);
    scene->AddSystem(new InputSystem());
    scene->AddSystem(renderSystem);
    scene->AddSystem(new SphericalControlSystem(0.3, 1.3));

    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new SphericalTransformComponent();
    auto cameraComponent = new SphericalCameraComponent();
    cameraComponent->SetFovY(XM_PI / 3);
    cameraEntity->AddComponent<SphericalTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<SphericalCameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new SphericalExpFogEffect(earthTexture, 0.4, DirectX::Colors::PowderBlue);

    auto entity1 = new Entity(), entity2 = new Entity();

    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(0.12, 20, 20);
    smc->SetEffect(effect);


    cameraComponent->SetFovY(XM_PI / 3); //эксперимент с видимостью
    int sphereCount = 6;
    for (int i = 0; i < sphereCount; i++)
    {
        auto transformComponent = new SphericalTransformComponent(0, 0, i * XM_PI / sphereCount);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);
        scene->AddEntity(entity);
    }


    auto bigSphereMesh = SphericalMeshComponentFactory::CreateSphericalSphere(0.85, 30, 30);
    bigSphereMesh->SetEffect(effect);

    {
        auto transformComponent = new SphericalTransformComponent(0, -XM_PIDIV2, 0);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(bigSphereMesh);
        //scene->AddEntity(entity);
    }

    scene->AddSystem(new TextPrintingSystem());
    auto textEntity = new Entity();
    textEntity->AddComponent<TextComponent>(new TextComponent([effect](double) {
        if (effect->GetMode())
            return "Spherical Space";
        else
            return "Elliptic Space";
        }, 10, 10, Alignment::UpLeft, DirectX::Colors::Black));
    scene->AddEntity(textEntity);

    scene->AddSystem(new ActionSystem<InputComponent>(
        [effect, renderSystem](Entity* pEntity, double deltaTime) {
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();

            if (kbs.D1)
                effect->SetMode(true);
            else if (kbs.D2)
                effect->SetMode(false);



        }));

    return game.StartGame();
}