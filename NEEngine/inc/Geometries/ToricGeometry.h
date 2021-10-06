#pragma once

// Common

#include <pch.h>

#include "Game.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "InputComponent.h"
#include "Entity.h"

// Components

#include "ComponentTypeManager.h"

#include "MeshComponent.h"
#include "CameraComponent.h"
#include "ToricTransformComponent.h"
#include "WalkComponent.h"
#include "InputSystem.h"
#include "UpdaterComponent.h"

#include "EuclideanMeshComponentFactory.h"

// Systems
#include "ToricRenderSystem.h"
#include "ToricControlSystem.h"
#include "UpdaterSystem.h"
#include "ActionSystem.h"

// Effects
#include "ToricExpFogEffect.h"

//TODO: может, вместе dimensions - специальный класс, определяющий геометрию пространства?

Scene * InitializeToricGeometry(const wchar_t * windowName, DirectX::XMVECTORF32 color, 
                                unsigned int replicationCount, DirectX::SimpleMath::Vector3 dimensions, double movementSpeed = 10., double rotationSpeed = 0.9,
                                bool isConsoleEnabled = false, bool isFullscreenEnabled = false, bool isVSyncEnabled = true)
{
    Game& game = Game::GetInstance();
    game.InitializeEngine(L"Test game", true, false, false);
    game.SetBackgroundColor(color);   //TODO: other place?
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();

    {
        auto componentTypeManager = game.GetComponentTypeManager();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<InputComponent>();
        componentTypeManager->RegisterComponentType<WalkComponent>();
        componentTypeManager->RegisterComponentType<ToricTransformComponent>();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<UpdaterComponent>();
        //meshcomp registered by default
        componentTypeManager->SetTypeAdditionEnded();
    }

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new UpdaterSystem());
    scene->AddSystem(new ToricControlSystem(movementSpeed, rotationSpeed));
    scene->AddSystem(new ToricRenderSystem(replicationCount, dimensions.x, dimensions.y, dimensions.z));

    return scene;
}