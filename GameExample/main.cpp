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


// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "BitmapRenderSystem.h"
#include "ActionSystem.h"
#include "CameraActionSystem.h"

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
        
        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* brickTexture = resourceManager->CreateTexture(L"brick.dds");
    Texture* characterTexture = resourceManager->CreateTexture(L"char2.dds");

    scene->AddSystem(new InputSystem());
    scene->AddSystem(new BitmapRenderSystem());

    auto cameraTransform = new TransformComponent(0, 0, -1, 0, 0, 0);


    scene->AddSystem(new ActionSystem<InputComponent, TransformComponent, WalkComponent>([](Entity* pEntity, double deltaTime) {
        auto pTransform = pEntity->GetTransform();
        auto pInput = pEntity->GetComponent<InputComponent>();
        auto kbs = pInput->GetKeyboardState();
        auto ms = pInput->GetMouseState();
        auto pWalk = pEntity->GetComponent<WalkComponent>();

        Vector3 up(0, deltaTime * pWalk->m_movementGain, 0);
        Vector3 right(deltaTime * pWalk->m_movementGain, 0, 0);


        if (kbs.D)
            pTransform->Move(right);
        if (kbs.A)
            pTransform->Move(-right);
        if (kbs.W)
            pTransform->Move(up);
        if (kbs.S)
            pTransform->Move(-up);

    }));

    Entity* cameraEntity = new Entity("camera1");
    auto cameraComponent = new CameraComponent(false);
    cameraComponent->SetOrthogonalWidth(30.);

    cameraEntity->SetTransform(cameraTransform);
    cameraEntity->AddComponent<CameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());

    scene->AddEntity(cameraEntity);
    scene->SetCamera(cameraEntity);


    auto charBitmap = new BitmapComponent(1, 1, characterTexture, false);
    auto charTransform = new TransformComponent(1, 3, 0, 0, 0, 0, 1, 1, 1);
    auto charWalkComponent = new WalkComponent(3, 4);
    auto charInputComponent = new InputComponent();

    Entity* character = new Entity();

    character->SetTransform(charTransform);
    character->AddComponent<BitmapComponent>(charBitmap);
    character->AddComponent<WalkComponent>(charWalkComponent);
    character->AddComponent<InputComponent>(charInputComponent);
    
    //cameraTransform->SetParent(charTransform);

    scene->AddEntity(character);

    return game.StartGame();
}




























/*
    MeshComponent::VertexPosTex vertices[8] = {
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
    auto m = new MeshComponent(8, vertices, 36, indices);
*/