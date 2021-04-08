#pragma once

#include <pch.h>

#include "Game.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "InputComponent.h"
#include "Entity.h"

// Components
#include "ComponentTypeManager.h"

#include "TransformComponent.h"
#include "InputComponent.h"
#include "BitmapComponent.h"
#include "CameraComponent.h"
#include "WalkComponent.h"

#include "SphericalTransformComponent.h"
#include "SphericalMeshComponent.h"

// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "BitmapRenderSystem.h"
#include "ActionSystem.h"
#include "CameraActionSystem.h"

#include "SphericalRenderSystem.h"

//Effect
#include "SphericalExpFogEffect.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char * argv[])
{
    //todo: Component* -> Component&  ?

    Game& game = Game::GetInstance();
    game.InitializeEngine(L"Test game", true, false, false);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();

    {
        auto componentTypeManager = game.GetComponentTypeManager();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<InputComponent>();
        componentTypeManager->RegisterComponentType<BitmapComponent>();
        componentTypeManager->RegisterComponentType<WalkComponent>();

        componentTypeManager->RegisterComponentType<SphericalTransformComponent>();
        componentTypeManager->RegisterComponentType<SphericalMeshComponent<VertexPosTex>>();

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* brickTexture = resourceManager->CreateTexture(L"brick.dds");
    Texture* characterTexture = resourceManager->CreateTexture(L"char2.dds");

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new SphericalRenderSystem());
    scene->AddSystem(new BitmapRenderSystem());

    auto cameraTransform = new TransformComponent(0, 0, -20, 0, 0, 0);


    scene->AddSystem(new ActionSystem<InputComponent, SphericalTransformComponent, WalkComponent>([](Entity* pEntity, double deltaTime) {
        auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
        auto pInput = pEntity->GetComponent<InputComponent>();
        auto kbs = pInput->GetKeyboardState();
        auto ms = pInput->GetMouseState();
        auto pWalk = pEntity->GetComponent<WalkComponent>();


        Vector3 up(0, deltaTime * pWalk->m_movementGain, 0);
        Vector3 right(deltaTime * pWalk->m_movementGain, 0, 0);
        Vector3 fwd(0, 0, deltaTime * pWalk->m_movementGain);


        if (kbs.D)
            pTransform->Move(right);
        if (kbs.A)
            pTransform->Move(-right);
        if (kbs.W)
            pTransform->Move(up);
        if (kbs.S)
            pTransform->Move(-up);
        if (kbs.R)
            pTransform->Move(fwd);
        if (kbs.F)
            pTransform->Move(-fwd);

    }));

    Entity* cameraEntity = new Entity("camera1");
    auto cameraComponent = new CameraComponent(true);
    cameraComponent->SetOrthogonalWidth(30.);

    cameraEntity->SetTransform(cameraTransform);
    cameraEntity->AddComponent<CameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());

    scene->AddEntity(cameraEntity);
    scene->SetCamera(cameraEntity);


    //auto charTransform = new TransformComponent(1, 3, 0, 0, 0, 0, 1, 1, 1);
    auto charWalkComponent = new WalkComponent(3, 4);
    auto charInputComponent = new InputComponent();

    Entity* test3D = new Entity();
    auto stc = new SphericalTransformComponent();
    test3D->AddComponent<SphericalTransformComponent>(stc);

    VertexPosTex vertices[3] = {
       { XMFLOAT4(-10.0f, -10.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) }, // 0
       { XMFLOAT4(-10.0f,  10.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) }, // 1
       { XMFLOAT4(10.0f,  10.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) }, // 2
    };

    WORD indices[3] =
    {
        0, 1, 2,
    };
    //на данный момент дефолтная система рендеринга отключена (тк рендерит все с не-null VertexTexMeshComponent)
    
    auto effect = new SphericalExpFogEffect(brickTexture);
    
    auto smc = new SphericalMeshComponent<VertexPosTex>(3, vertices, 3, indices);
    smc->SetTexture(brickTexture);
    smc->SetEffect(effect);
    test3D->AddComponent<SphericalMeshComponent<VertexPosTex>>(smc);
    scene->AddEntity(test3D);



    Entity* test3D_2 = new Entity();
    auto stc_2 = new SphericalTransformComponent();
    test3D_2->AddComponent<SphericalTransformComponent>(stc_2);

    VertexPosTex vertices2[3] = {
       { XMFLOAT4(-5.0f, -10.0f, 0.5f, 1.0f), XMFLOAT2(0.0f, 0.0f) }, // 0
       { XMFLOAT4(15.0f,  -10.0f, 0.5f, 1.0f), XMFLOAT2(0.0f, 1.0f) }, // 1
       { XMFLOAT4(15.0f,  10.0f, 0.5f, 1.0f), XMFLOAT2(1.0f, 1.0f) }, // 2
    };

    WORD indices2[3] =
    {
        0, 2, 1,
    };

    auto smc2 = new SphericalMeshComponent<VertexPosTex>(3, vertices2, 3, indices2);
    smc2->SetTexture(brickTexture);
    smc2->SetEffect(effect);
    test3D_2->AddComponent<SphericalMeshComponent<VertexPosTex>>(smc2);
    test3D_2->AddComponent<WalkComponent>(charWalkComponent);
    test3D_2->AddComponent<InputComponent>(charInputComponent);
    scene->AddEntity(test3D_2);


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