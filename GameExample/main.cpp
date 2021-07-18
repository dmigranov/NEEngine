#pragma once

#include "Geometries/SphericalEllipticGeometry.h"
#include "WalkComponent.h"
#include "InputSystem.h"

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

        componentTypeManager->RegisterComponentType<SphericalTransformComponent>();
        componentTypeManager->RegisterComponentType<SphericalCameraComponent>();
        componentTypeManager->RegisterComponentType<CameraComponent>();

        //transfcomp и meshcom зарегистр по умолчанию... 

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* brickTexture = resourceManager->CreateTexture(L"brick.dds");
    Texture* earthTexture = resourceManager->CreateTexture(L"earth8k.dds");
    Texture* characterTexture = resourceManager->CreateTexture(L"char2.dds");

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new SphericalRenderSystem());
    scene->AddSystem(new SphericalControlSystem(0.3, 1.3));
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

            /*
            if (kbs.D)
                pTransform->SetWorld(SphericalRotationXW(deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());
            if (kbs.A)
                pTransform->SetWorld(SphericalRotationXW(-deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());
            if (kbs.W)
                pTransform->SetWorld(SphericalRotationYW(deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());
            if (kbs.S)
                pTransform->SetWorld(SphericalRotationYW(-deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());
            */
            if (kbs.R)
                pTransform->SetWorld(SphericalRotationZW(deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());
            if (kbs.F)
                pTransform->SetWorld(SphericalRotationZW(-deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());

            //pTransform->Move(-fwd); //должно быть так todo
        }));


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

    auto testEntity = new Entity();
    auto stc = new SphericalTransformComponent();

    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(0.3, 20, 20);
    smc->SetEffect(effect);
    testEntity->AddComponent<SphericalTransformComponent>(stc);
    testEntity->AddComponent<MeshComponent>(smc);
    testEntity->AddComponent<WalkComponent>(charWalkComponent);
    testEntity->AddComponent<InputComponent>(charInputComponent);
    scene->AddEntity(testEntity);

    scene->AddSystem(new ActionSystem<InputComponent>(
        [effect](Entity* pEntity, double deltaTime) {
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();
            auto sphEff = (SphericalExpFogEffect*)effect;

            if (kbs.D1)
                sphEff->SetMode(true);
            else if (kbs.D2)
                sphEff->SetMode(false);
        }));

    return game.StartGame();
}