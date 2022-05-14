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
    game.InitializeEngine(1280, 720, L"Spherical & Elliptic Spaces", true, false, false);
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

    Texture* earthTexture = new Texture(L"earth8k.dds");

    int sphereCount;
    if (argc < 2)
    {
        std::cerr << "No input parameter was present, sphereCount = 100 (default)" << std::endl;
        sphereCount = 100;
    }
    else
    {
        char* sphereCountStr = argv[1];
        try {
            int number = std::stoi(sphereCountStr);
            if (number > 0)
                sphereCount = number;
            else
                sphereCount = 100;
        }
        catch (std::exception const& e) {
            // Could not be parsed into a number
            std::cerr << "Couldn't parse, sphereCount = 100 (default)" << std::endl;
            sphereCount = 100;
        }
    }

    auto renderSystem = new SphericalRenderSystem();
    renderSystem->SetRadius(radius);
    scene->AddSystem(new InputSystem());
    scene->AddSystem(renderSystem);
    scene->AddSystem(new SphericalControlSystem(0.3, 1.3));

    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new SphericalTransformComponent();
    auto cameraComponent = new SphericalCameraComponent();
    cameraEntity->AddComponent<SphericalTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<SphericalCameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new SphericalExpFogEffect(earthTexture, 0.4, DirectX::Colors::PowderBlue);

    auto charWalkComponent = new WalkComponent(3, 4);
    auto charInputComponent = new InputComponent();

    auto entity1 = new Entity(), entity2 = new Entity();

    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(0.1, 20, 20);
    smc->SetEffect(effect);

    cameraComponent->SetFovY(XM_PI / 2); //эксперимент с видимостью

    RandomSphericalGenerator generator(radius);   
    auto entities = new Entity * [sphereCount];
    for (int i = 0; i < sphereCount; i++)
    {
        auto point = generator.GeneratePoint();

        auto transformComponent = new SphericalTransformComponent();
        transformComponent->MoveAbsolute(point.x, point.y, point.z, point.w); //!!!

        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);

        scene->AddEntity(entity);
        entities[i] = entity;
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