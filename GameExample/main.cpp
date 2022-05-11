#pragma once

#include "Geometries/HyperbolicGeometry.h"
#include "WalkComponent.h"
#include "InputSystem.h"
#include "ActionSystem.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
    Game& game = Game::GetInstance();
    game.InitializeEngine(1280, 720, L"Test game", true, false, false);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();

    {
        auto componentTypeManager = game.GetComponentTypeManager();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<InputComponent>();
        componentTypeManager->RegisterComponentType<WalkComponent>();

        componentTypeManager->RegisterComponentType<HyperbolicTransformComponent>();
        componentTypeManager->RegisterComponentType<HyperbolicCameraComponent>();

        //transfcomp и meshcom зарегистр по умолчанию... 

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* earthTexture = new Texture(L"earth8k.dds");

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new HyperbolicRenderSystem());
    scene->AddSystem(new HyperbolicControlSystem(0.3, 1.3));
    scene->AddSystem(new ActionSystem<InputComponent, HyperbolicTransformComponent, WalkComponent>(
        [](Entity* pEntity, double deltaTime) {
            auto pTransform = pEntity->GetComponent<HyperbolicTransformComponent>();
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

        }));


    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new HyperbolicTransformComponent();
    auto cameraComponent = new HyperbolicCameraComponent();
    cameraComponent->SetFovY(XM_PI/3);
    cameraEntity->AddComponent<HyperbolicTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<HyperbolicCameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    //cameraEntity->AddComponent<WalkComponent>(new WalkComponent(3, 4));

    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new HyperbolicExpFogEffect(earthTexture, 0.3, DirectX::Colors::PowderBlue);


    auto charWalkComponent = new WalkComponent(3, 4);
    auto charInputComponent = new InputComponent();

    auto entity1 = new Entity(), entity2 = new Entity(), entity3 = new Entity(), entity4 = new Entity();

    auto smc = HyperbolicMeshComponentFactory::CreateHyperbolicSphere(1, 20, 20);
    smc->SetEffect(effect);

    auto tc1 = new HyperbolicTransformComponent(0, 0, 0);
    auto tc2 = new HyperbolicTransformComponent(2.3, 0, 0);
    auto tc3 = new HyperbolicTransformComponent(4.6, 0, 0);
    auto tc4 = new HyperbolicTransformComponent(6.9, 0, 0);

    entity1->AddComponent<HyperbolicTransformComponent>(tc1);
    entity1->AddComponent<MeshComponent>(smc);
    entity1->AddComponent<UpdaterComponent>(new UpdaterComponent([](double deltaTime, Entity* pEntity) {

        }));
    scene->AddEntity(entity1);

    /*
    entity2->AddComponent<HyperbolicTransformComponent>(tc2);
    entity2->AddComponent<MeshComponent>(smc);
    scene->AddEntity(entity2);

    entity3->AddComponent<HyperbolicTransformComponent>(tc3);
    entity3->AddComponent<MeshComponent>(smc);
    scene->AddEntity(entity3);

    entity4->AddComponent<HyperbolicTransformComponent>(tc4);
    entity4->AddComponent<MeshComponent>(smc);
    scene->AddEntity(entity4);
    */

    return game.StartGame();
}