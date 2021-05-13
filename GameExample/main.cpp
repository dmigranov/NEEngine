#pragma once

#include <pch.h>

#include "Game.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "InputComponent.h"
#include "Entity.h"

// Components
#include "ComponentTypeManager.h"

#include "InputComponent.h"
#include "BitmapComponent.h"
#include "WalkComponent.h"
#include "MeshComponent.h"
#include "TransformComponent.h"


#include "MeshComponentFactory.h"
#include "EuclideanMeshComponentFactory.h"

// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "ActionSystem.h"

#include "ToricRenderSystem.h"

#include "CameraActionSystem.h"


//Effect
#include "ToricExpFogEffect.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char * argv[])
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

        componentTypeManager->RegisterComponentType<CameraComponent>();

        //transfcomp и meshcom зарегистр по умолчанию...

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* brickTexture = resourceManager->CreateTexture(L"brick.dds");
    Texture* earthTexture = resourceManager->CreateTexture(L"earth8k.dds");
    Texture* characterTexture = resourceManager->CreateTexture(L"char2.dds");
    Texture* cubemapTexture = resourceManager->CreateTexture(L"cubemap.dds");

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new CameraActionSystem());
    scene->AddSystem(new ToricRenderSystem(5, 30, 30, 30));
    /*scene->AddSystem(new ActionSystem<InputComponent, SphericalTransformComponent, WalkComponent>(
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
            pTransform->SetWorld(SphericalRotationZW(deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());
        if (kbs.F)
            pTransform->SetWorld(SphericalRotationZW(-deltaTime * pWalk->m_movementGain) * pTransform->GetWorld());
       
        //pTransform->Move(-fwd); //должно быть так todo
    }));*/


    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new TransformComponent();
    auto cameraComponent = new CameraComponent();
    cameraEntity->AddComponent<TransformComponent>(cameraTransform);
    cameraEntity->AddComponent<CameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent); 
    scene->AddEntity(cameraEntity);


    auto effect = new ToricExpFogEffect(cubemapTexture, 0.005, DirectX::Colors::PowderBlue);


    auto charWalkComponent = new WalkComponent(3, 4);
    auto charInputComponent = new InputComponent();
   
    auto testEntity = new Entity();
    auto stc = new TransformComponent();

    auto smc = EuclideanMeshComponentFactory::CreateCube(3);
    smc->SetEffect(effect);
    testEntity->AddComponent<TransformComponent>(stc);
    testEntity->AddComponent<MeshComponent>(smc);
    testEntity->AddComponent<WalkComponent>(charWalkComponent);
    testEntity->AddComponent<InputComponent>(charInputComponent);
    scene->AddEntity(testEntity);


    return game.StartGame();
}




























/*
    VertexTexMeshComponent::VertexPosTex vertices[8] = {
        { XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT2(0, 0) }, // 0
        { XMFLOAT4(-1.0f,  1.0f, -1.0f, 1.0f), XMFLOAT2(0, 1) }, // 1
        { XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f), XMFLOAT2(1, 1)}, // 2
        { XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT2(1, 0)}, // 3
        { XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f),  XMFLOAT2(0, 0) }, // 4
        { XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f), XMFLOAT2(0, 1)}, // 5
        { XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f), XMFLOAT2(1, 1) }, // 6
        { XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f), XMFLOAT2(0, 1) }  // 7
    };

    WORD indices[36] =
    {
        0, 1, 2, 0, 2, 3,
        4, 6, 5, 4, 7, 6,
        4, 5, 1, 4, 1, 0,
        3, 2, 6, 3, 6, 7,
        1, 5, 6, 1, 6, 2,
        3, 4, 0, 7, 4, 3
    };
    auto m = new VertexTexMeshComponent(8, vertices, 36, indices);
*/