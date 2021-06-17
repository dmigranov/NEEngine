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

    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new TransformComponent();
    auto cameraComponent = new CameraComponent();
    cameraEntity->AddComponent<TransformComponent>(cameraTransform);
    cameraEntity->AddComponent<CameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);


    auto effect = new ToricExpFogEffect(cubemapTexture, 0.02, DirectX::Colors::PowderBlue);


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