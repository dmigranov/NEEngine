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

#include "Force.h"


// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "BitmapRenderSystem.h"
#include "ActionSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"

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
    Texture* characterTexture = resourceManager->CreateTexture(L"char2.dds");



    scene->AddSystem(new InputSystem());
    scene->AddSystem(new BitmapRenderSystem());
    scene->AddSystem(new PhysicsSystem());
    scene->AddSystem(new CollisionSystem());

    auto cameraTransform = new TransformComponent(0, 0, -1, 0, 0, 0);

    scene->AddSystem(new ActionSystem({ ComponentType::InputComponentType, ComponentType::TransformComponentType, ComponentType::WalkComponentType, ComponentType::PhysicsComponentType },
        [](Entity* pEntity, double deltaTime) {
        //todo: в будущем обновлять тут скорость, а положение менять в физике?

        auto pTransform = pEntity->GetTransform();
        auto pInput = (InputComponent*)pEntity->GetComponent(ComponentType::InputComponentType);
        auto kbs = pInput->GetKeyboardState();
        auto ms = pInput->GetMouseState();
        auto pWalk = (WalkComponent*)pEntity->GetComponent(ComponentType::WalkComponentType);
        auto pPhysics = (PhysicsComponent*)pEntity->GetComponent(ComponentType::PhysicsComponentType);

        Vector3 up(0, deltaTime * pWalk->m_movementGain, 0);
        Vector3 right(deltaTime * pWalk->m_movementGain, 0, 0);


        static bool isRightPressed;
        if (kbs.D)
        {
            if (!isRightPressed)
            {
                pPhysics->AddForce("right", Force(Vector3(10., 0, 0.)));                
                isRightPressed = true;
            }

        }
        else if (isRightPressed)
        {
            pPhysics->RemoveForce("right");
            isRightPressed = false;
        }

        static bool isLeftPressed;
        if (kbs.A)
        {
            if (!isLeftPressed)
            {
                pPhysics->AddForce("left", Force(Vector3(-10., 0, 0.)));

                isLeftPressed = true;
            }
        }
        else if (isLeftPressed)
        {
            pPhysics->RemoveForce("left");
            isLeftPressed = false;
        }

        static bool isSpacePressed;
        if (kbs.Space)
        {
            if(!isSpacePressed)
            {
                pPhysics->AddForce("jump", Force(Vector3(0., 15, 0.)));
                isSpacePressed = true;
            }
        }
        else if (isSpacePressed)
        {
            pPhysics->RemoveForce("jump");
            isSpacePressed = false;
        }
    }));


    Entity* cameraEntity = new Entity("camera1");
    auto cameraComponent = new CameraComponent(false);
    cameraComponent->SetOrthogonalWidth(30.);

    cameraEntity->SetTransform(cameraTransform);
    cameraEntity->AddComponent(ComponentType::CameraComponentType, cameraComponent);

    scene->AddEntity(cameraEntity);
    scene->SetCamera(cameraEntity);

    auto brickCollisionComponent = new CollisionComponent([](Entity* pThisEntity, Entity* pOtherEntity, double deltaTime) {}, -0.5, -0.5, 0.5, 0.5);


    auto brickBitmap = new BitmapComponent(1, 1, brickTexture, false);
    constexpr int wh = 25;
    constexpr int brickCount = wh * wh - (wh -2) * (wh - 2);
    Entity* bricks[brickCount];
    TransformComponent* transforms[brickCount];
    int j = 0;
    for (int i = 0; i < wh * wh; i++)
    {
        int ColumnNumber = i % wh;
        int RowNumber = i / wh;
        if (ColumnNumber == 0 || RowNumber == 0 || ColumnNumber == wh - 1 || RowNumber == wh - 1)
        {
            auto e = bricks[j] = new Entity();
            auto t = transforms[j] = new TransformComponent(ColumnNumber, RowNumber, 1, 0, 0, 0, 1, 1, 1);
            j++;
            e->SetTransform(t);
            e->AddComponent(ComponentType::BitmapComponentType, brickBitmap);
            e->AddComponent(ComponentType::CollisionComponentType, brickCollisionComponent);
            scene->AddEntity(e);
        }
    }


    auto charBitmap = new BitmapComponent(1, 1, characterTexture, false);
    auto charTransform = new TransformComponent(1, 3, 0, 0, 0, 0, 1, 1, 1);
    auto charWalkComponent = new WalkComponent(3, 4);
    auto charPhysicsComponent = new PhysicsComponent(1.);
    auto charInputComponent = new InputComponent();
    auto charCollisionComponent = new CollisionComponent([](Entity* pThisEntity, Entity* pOtherEntity, double deltaTime) {

        auto pPhysics = (PhysicsComponent*)pThisEntity->GetComponent(ComponentType::PhysicsComponentType);
        auto pTransform = (TransformComponent*)pThisEntity->GetComponent(ComponentType::TransformComponentType);

        auto velocity = pPhysics->GetVelocity();
        auto acceleration = pPhysics->GetAcceleration();

        pTransform->Move(-velocity * deltaTime);
        pPhysics->SetAcceleration(Vector3::Zero);
        pPhysics->SetVelocity(Vector3::Zero);
    }, -0.5, -0.5, 0.5, 0.5);

    charPhysicsComponent->AddForce("gravity", Force(Vector3(0, -9.8, 0)));
    charPhysicsComponent->AddForce("drag", Force([charPhysicsComponent](Force& force)
    {
        auto v = charPhysicsComponent->GetVelocity();
        force.SetVector(-v/2);
    }));

    Entity* character = new Entity();

    character->SetTransform(charTransform);
    character->AddComponent(ComponentType::BitmapComponentType, charBitmap);
    character->AddComponent(ComponentType::WalkComponentType, charWalkComponent);
    character->AddComponent(ComponentType::PhysicsComponentType, charPhysicsComponent);
    character->AddComponent(ComponentType::InputComponentType, charInputComponent);
    character->AddComponent(ComponentType::CollisionComponentType, charCollisionComponent);


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