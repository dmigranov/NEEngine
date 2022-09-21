#pragma once

#include "Geometries/ToricGeometry.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
    auto scene = InitializeToricGeometry(L"Test game", DirectX::Colors::PowderBlue,
        19, DirectX::SimpleMath::Vector3(37, 37, 37), 20, 0.7,
        true, false, false);

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

    auto effect = new ToricExpFogEffect(cubemapTexture, 0.006, DirectX::Colors::PowderBlue);

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

            Vector3 up(0, deltaTime * 200, 0);
            Vector3 right(deltaTime * 200, 0, 0);
            Vector3 fwd(0, 0, deltaTime * 200);

            if (kbs.R)
                pTransform->Move(up);
            if (kbs.F)
                pTransform->Move(-up);

            if (kbs.T)
                pTransform->Rotate(deltaTime, 0, 0);
            if (kbs.Y)
                pTransform->Rotate(-deltaTime, 0, 0);
            if (kbs.G)
                pTransform->Rotate(0, deltaTime, 0);
            if (kbs.H)
                pTransform->Rotate(0, -deltaTime, 0);
            if (kbs.B)
                pTransform->Rotate(0, 0, deltaTime);
            if (kbs.N)
                pTransform->Rotate(0, 0, -deltaTime);

            }));
    }

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
            //pEntity->GetComponent<ToricTransformComponent>()->Rotate(0, -3 * delta, 0); //вокруг собственной оси
            }));
    }

    return Game::GetInstance().StartGame();
}