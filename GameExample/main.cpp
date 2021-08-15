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
    game.InitializeEngine(L"Test game", true, false, false);
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

    Texture* brickTexture = resourceManager->CreateTexture(L"brick.dds");
    Texture* earthTexture = resourceManager->CreateTexture(L"earth8k.dds");
    Texture* characterTexture = resourceManager->CreateTexture(L"char2.dds");

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new HyperbolicRenderSystem());
    //scene->AddSystem(new HyperbolicControlSystem(0.3, 1.3));
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

            if (kbs.T)
                pTransform->Rotate(deltaTime, 0, 0);
            if (kbs.G)
                pTransform->Rotate(0, deltaTime, 0);
            if (kbs.B)
                pTransform->Rotate(0, 0, deltaTime);
        }));


    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new HyperbolicTransformComponent();
    auto cameraComponent = new HyperbolicCameraComponent();
    cameraEntity->AddComponent<HyperbolicTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<HyperbolicCameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    cameraEntity->AddComponent<WalkComponent>(new WalkComponent(3, 4));

    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new HyperbolicExpFogEffect(earthTexture, 0.1, DirectX::Colors::PowderBlue);


    auto charWalkComponent = new WalkComponent(3, 4);
    auto charInputComponent = new InputComponent();

    auto entity1 = new Entity(), entity2 = new Entity();

    auto smc = HyperbolicMeshComponentFactory::CreateHyperbolicSphere(0.3, 20, 20);
    smc->SetEffect(effect);

    auto tc1 = new HyperbolicTransformComponent(0, 0, 2);
    auto tc2 = new HyperbolicTransformComponent(1, 0, 0);

    entity1->AddComponent<HyperbolicTransformComponent>(tc1);
    entity1->AddComponent<MeshComponent>(smc);
    //entity1->AddComponent<WalkComponent>(charWalkComponent);
    //entity1->AddComponent<InputComponent>(charInputComponent);
    scene->AddEntity(entity1);

    entity2->AddComponent<HyperbolicTransformComponent>(tc2);
    entity2->AddComponent<MeshComponent>(smc);
    scene->AddEntity(entity2);

    return game.StartGame();
}