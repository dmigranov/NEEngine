﻿#pragma once

#include "Geometries/ToricGeometry.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
    int replicationCount = 8;
    bool isDefault = true;
    if (argc >= 2)
    {
        char* sphereCountStr = argv[1];
        try {
            int number = std::stoi(sphereCountStr);
            if (number > 0)
            {
                replicationCount = number;
                isDefault = false;
            }
        }
        catch (std::exception const& e) {
            // Could not be parsed into a number
        }
    }

    long totalReplicationCount = (2 * replicationCount + 1);
    totalReplicationCount = totalReplicationCount * totalReplicationCount * totalReplicationCount;

    auto scene = InitializeToricGeometry(L"Test game", DirectX::Colors::PowderBlue,
        replicationCount, DirectX::SimpleMath::Vector3(10, 10, 10), 20, 0.9,
        true, false, false);

    if (isDefault)
        std::cerr << "Couldn't parse, replication count = 8 (default)" << std::endl;
    std::cerr << "Total replication count: " << totalReplicationCount << std::endl;

    auto resourceManager = Game::GetInstance().GetResourceManager();
    Texture* cubemapTexture = new Texture(L"cubemap.dds");


    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new ToricTransformComponent();
    auto cameraComponent = new CameraComponent();
    cameraComponent->SetFovY(DirectX::XM_PI / 3);
    cameraEntity->AddComponent<ToricTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<CameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new ToricExpFogEffect(cubemapTexture, 0.001, DirectX::Colors::PowderBlue);

    //auto charWalkComponent = new WalkComponent(200, 4);
    auto charInputComponent = new InputComponent();

    auto entity1 = new Entity();
    auto ttc1 = new ToricTransformComponent();
    {
        auto tmc1 = EuclideanMeshComponentFactory::CreateCube(3);
        tmc1->SetEffect(effect);
        entity1->AddComponent<ToricTransformComponent>(ttc1);
        entity1->AddComponent<MeshComponent>(tmc1);
        entity1->AddComponent<InputComponent>(charInputComponent);
        scene->AddEntity(entity1);

        entity1->AddComponent<UpdaterComponent>(new UpdaterComponent([](double deltaTime, Entity* pEntity) {
            auto pTransform = pEntity->GetComponent<ToricTransformComponent>();
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();
            auto ms = pInput->GetMouseState();

            Vector3 up(0, deltaTime * 2, 0);
            Vector3 right(deltaTime * 2, 0, 0);
            Vector3 fwd(0, 0, deltaTime * 2);

            pTransform->Rotate(up);
            }));
    }

    /*
    {
        auto childEntity = new Entity();
        auto ttc2 = new ToricTransformComponent(3, 0, 0);
        ttc2->SetParent(ttc1);
        auto tmc2 = EuclideanMeshComponentFactory::CreateCube(1);
        tmc2->SetEffect(effect);
        childEntity->AddComponent<ToricTransformComponent>(ttc2);
        childEntity->AddComponent<MeshComponent>(tmc2);
        scene->AddEntity(childEntity);

        childEntity->AddComponent<UpdaterComponent>(new UpdaterComponent([](double delta, Entity* pEntity) {
            pEntity->GetComponent<ToricTransformComponent>()->RotateGlobal(0, 2 * delta, 0);
            }));
    }
    */

    return Game::GetInstance().StartGame();
}