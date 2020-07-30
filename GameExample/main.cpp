#include <pch.h>

#include "Game.h"
#include "Scene.h"
#include "Camera.h"

#include "ResourceManager.h"
#include "InputComponent.h"

#include "Entity.h"

// Components
#include "ComponentType.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "InputComponent.h"
#include "BitmapComponent.h"
#include "CameraComponent.h"
#include "WalkComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"


// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "BitmapRenderSystem.h"
#include "ActionSystem.h"
#include "PhysicsSystem.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
    //todo: перенастроить SwapChain, чтобы был Swapping!

    Game& game = Game::GetInstance();
    game.InitializeEngine(hInstance, nCmdShow, L"Test game", false, false);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();
    Texture* brickTexture = resourceManager->CreateTexture(L"brick.dds");
    Texture* characterTexture = resourceManager->CreateTexture(L"char.dds");



    scene->AddSystem(new InputSystem());
    scene->AddSystem(new BitmapRenderSystem());
    scene->AddSystem(new PhysicsSystem());

    auto cameraTransform = new TransformComponent(0, 0, -1, 0, 0, 0);

    scene->AddSystem(new ActionSystem({ ComponentType::InputComponentType, ComponentType::TransformComponentType, ComponentType::WalkComponentType, ComponentType::PhysicsComponentType },
        [](Entity* pEntity, DWORD deltaTime) {
        //todo: в будущем обновлять тут скорость, а положение менять в физике?

        auto pTransform = pEntity->GetTransform();
        auto pInput = (InputComponent*)pEntity->GetComponent(ComponentType::InputComponentType);
        auto kbs = pInput->GetKeyboardState();
        auto ms = pInput->GetMouseState();
        auto pWalk = (WalkComponent*)pEntity->GetComponent(ComponentType::WalkComponentType);
        auto pPhysics = (PhysicsComponent*)pEntity->GetComponent(ComponentType::PhysicsComponentType);

        Vector3 up(0, deltaTime * pWalk->m_movementGain, 0);
        Vector3 right(deltaTime * pWalk->m_movementGain, 0, 0);

        if (kbs.W)
            pTransform->Move(up);
        if (kbs.S)
            pTransform->Move(-up);
        if (kbs.A)
            pTransform->Move(-right);
        if (kbs.D)
            pTransform->Move(right);


        /*static bool isLeftForceApplied = false;
        if (kbs.Left)
        {
            if(!isLeftForceApplied)
            {
                pPhysics->AddForce("left", Vector3(-1., 0., 0.));
                isLeftForceApplied = true;
            }
            else
            {
                pPhysics->RemoveForce("left");
                isLeftForceApplied = false;
            }
        }
        else
            isLeftForceApplied = false;
            */

            /*if (kbs.D1)
                pEntity->SetTransform(cameraTransform1);
            else if (kbs.D2)
                pEntity->SetTransform(cameraTransform2);*/


    }));


    Entity* cameraEntity = new Entity("camera1");
    auto cameraComponent = new CameraComponent(false);

    cameraEntity->SetTransform(cameraTransform);
    cameraEntity->AddComponent(ComponentType::CameraComponentType, cameraComponent);

    scene->AddEntity(cameraEntity);
    scene->SetCamera(cameraEntity);



    auto brickBitmap = new BitmapComponent(1, 1, brickTexture, false);
    Entity* e1 = new Entity();
    auto transform1 = new TransformComponent(0, 0, 1, 0, 0, 0, 1, 1, 1);
    e1->SetTransform(transform1);
    e1->AddComponent(ComponentType::BitmapComponentType, brickBitmap);
    scene->AddEntity(e1);

    auto transform2 = new TransformComponent(1, 0, 1, 0, 0, 0, 1, 1, 1);
    Entity* e2 = new Entity();
    e2->SetTransform(transform2);
    e2->AddComponent(ComponentType::BitmapComponentType, brickBitmap);
    scene->AddEntity(e2);

    auto charBitmap = new BitmapComponent(1, 1, characterTexture, false);
    auto charTransform = new TransformComponent(1, 4, 0, 0, 0, 0, 1, 1, 1);
    auto charWalkComponent = new WalkComponent(0.003, 0.004);
    auto charPhysicsComponent = new PhysicsComponent(1.);
    auto charInputComponent = new InputComponent();
    //auto charCollisionComponent = new CollisionComponent(-0.5, -0.5, 0.5, 0.5);

    //charPhysicsComponent->AddForce("gravity", Vector3(0, 0, 0));

    Entity* character = new Entity();

    character->SetTransform(charTransform);
    character->AddComponent(ComponentType::BitmapComponentType, charBitmap);
    character->AddComponent(ComponentType::WalkComponentType, charWalkComponent);
    character->AddComponent(ComponentType::PhysicsComponentType, charPhysicsComponent);
    character->AddComponent(ComponentType::InputComponentType, charInputComponent);

    cameraTransform->SetParent(charTransform);

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