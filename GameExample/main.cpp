#pragma once

#include "Geometries/ToricGeometry.h"
#include "WalkComponent.h"
#include "InputSystem.h"

#include "UpdaterSystem.h"
#include "UpdaterComponent.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
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
        componentTypeManager->RegisterComponentType<ToricTransformComponent>();
        componentTypeManager->RegisterComponentType<CameraComponent>();

        //transfcomp и meshcom зарегистр по умолчанию...

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* cubemapTexture = resourceManager->CreateTexture(L"cubemap.dds");

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new ToricControlSystem(10., 0.9));
    scene->AddSystem(new ToricRenderSystem(8, 30, 30, 30));
    scene->AddSystem(new ActionSystem<InputComponent, ToricTransformComponent, WalkComponent>(
        [](Entity* pEntity, double deltaTime) {
            auto pTransform = pEntity->GetComponent<ToricTransformComponent>();
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

    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new ToricTransformComponent();
    auto cameraComponent = new CameraComponent();
    cameraEntity->AddComponent<ToricTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<CameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new ToricExpFogEffect(cubemapTexture, 0.015, DirectX::Colors::PowderBlue);


    auto charWalkComponent = new WalkComponent(200, 4);
    auto charInputComponent = new InputComponent();

    auto entity1 = new Entity();
    auto ttc1 = new ToricTransformComponent();
    {
        auto tmc1 = EuclideanMeshComponentFactory::CreateCube(3);
        tmc1->SetEffect(effect);
        entity1->AddComponent<ToricTransformComponent>(ttc1);
        entity1->AddComponent<MeshComponent>(tmc1);
        entity1->AddComponent<WalkComponent>(charWalkComponent);
        entity1->AddComponent<InputComponent>(charInputComponent);
        scene->AddEntity(entity1);
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


    }

    return game.StartGame();
}