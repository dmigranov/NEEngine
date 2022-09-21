﻿#pragma once

#include "main.h"

#include "InputSystem.h"
#include "TextPrintingSystem.h"
#include "TextComponent.h"
#include "RandomSphericalGenerator.h"
#include "SphericalMath.h"
#include "EuclideanMeshComponentFactory.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
    //todo: были какие-то щелчки все равно

    double radius = 1.;

    Game& game = Game::GetInstance();
    game.InitializeEngine(1280, 720, L"Friedmann Model Visualization", true, false, true);
    game.SetBackgroundColor(DirectX::Colors::Black);   //todo: перенести
    Scene* scene = game.GetScene();

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

    Texture* earthTexture = new Texture(L"earth8k.dds");
    Texture* rainbowTexture2 = new Texture(L"rainbow4.dds");
    Texture* greenTexture = new Texture(L"green_texture.dds");

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
    auto pInputComponent = new InputComponent();
    cameraEntity->AddComponent<InputComponent>(pInputComponent);
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);

    auto effect = new SphericalDopplerEffect(greenTexture, rainbowTexture2, 0.1, DirectX::Colors::Black);
    //auto effect = new SphericalExpFogEffect(earthTexture, 0.15, DirectX::Colors::Black);

    auto pointEffect = new SphericalExpFogPointEffect(0.1, DirectX::Colors::Black);

    double objectRadius = 0.1; //0.49
    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(objectRadius, 15, 15);
    smc->SetEffect(effect);

    //auto loadedMesh = EuclideanMeshComponentFactory::CreateMeshFromFile("mesh.sph");

    auto pointComp = SphericalMeshComponentFactory::CreateSphericalPoint();
    pointComp->SetEffect(pointEffect);

    // --- Uniform Distribution --- //

    RandomSphericalGenerator generator(radius);
    int sphereCount = 80; //100
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
        transformComponent->MoveAbsolute(point.x, point.y, point.z, point.w); //!!!

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

    System* controlSystem = nullptr;
    System* visibilitySystem = nullptr;
    System* radiusUpdateSystem = nullptr;
    System* animationSystem = nullptr;
    SelectionSystem* selectionSystem = nullptr;
    System* soundSystem = nullptr;

    auto timer = CreateFriedmannSystems(effect, cameraTransform, renderSystem, pInputComponent, objectRadius,
        &controlSystem, &visibilitySystem, &radiusUpdateSystem, &animationSystem, &selectionSystem, &soundSystem);

    scene->AddSystem(controlSystem);
    scene->AddSystem(visibilitySystem);
    scene->AddSystem(animationSystem);
    scene->AddSystem(selectionSystem);
    //scene->AddSystem(soundSystem);

    scene->AddSystem(radiusUpdateSystem);   // !!! has to be after all systems where simulation time changes!

    auto selectedObjects = new bool[sphereCount] {false};

    auto textEntity2 = new Entity();
    textEntity2->AddComponent<TextComponent>(new TextComponent([selectionSystem, cameraTransform](double delta) {

        auto pSelectedEntity = selectionSystem->GetSelectedEntity();

        std::stringstream ss;

        ss << std::fixed << std::setprecision(2);
        if (pSelectedEntity != nullptr)
        {
            ss << "Sphere " << selectionSystem->GetSelectedIndex() << std::endl;

            const auto& view = cameraTransform->GetView();
            auto pSphTransform = pSelectedEntity->GetComponent<SphericalTransformComponent>();
            auto sphPosWorld = pSphTransform->GetSphericalPosition();
            auto sphPosView = Vector4::Transform(sphPosWorld, view); //pos_view

            auto radius = SphericalEffect::GetRadius();
            double chi = acos(sphPosView.w / radius);
            if (sphPosView.z > 0)
                ss << "Front half" << std::endl;
            else {
                ss << "Back half" << std::endl;
                chi = XM_2PI - chi;
            }
            ss << "Chi: " << chi << std::endl;
            //ss << "Chi: " << SphericalDistance(Vector4(0, 0, 0, 1), sphPosView/radius, 1) << std::endl;
        }

        return ss.str();

        }, 10, 10, Alignment::DownRight, DirectX::Colors::White));

    scene->AddEntity(textEntity2);

    //auto test = Vector4::Transform(Vector4(0, 0, 0, 1), SphericalRotationYW(0.1));
    //std::cout << test.x << " " << test.y << " " << test.z << " " << test.w << " " << std::endl;
    //две строки сверху - доказательство использования вектор строк

    return game.StartGame();
}


// в общем: чтобы не надо было подключать библиотеки к примеру, нужно добавить их в библиотекаре
// но тогда потеряется отладочная информация...