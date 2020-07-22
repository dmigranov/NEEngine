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


// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "BitmapRenderSystem.h"
#include "ActionSystem.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
    Game& game = Game::GetInstance();
    game.InitializeEngine(hInstance, nCmdShow, L"Сф. и Элл. Пространства", false, false);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager(); 
    Texture* asphaltTexture = resourceManager->CreateTexture(L"cat.dds");



    scene->AddSystem(new InputSystem());
    scene->AddSystem(new BitmapRenderSystem());

    scene->AddSystem(new ActionSystem({ ComponentType::InputComponentType, ComponentType::TransformComponentType, ComponentType::WalkComponentType }, [](Entity* pEntity, DWORD deltaTime) {
        auto pTransform = pEntity->GetTransform();
        auto pInput = (InputComponent*)pEntity->GetComponent(ComponentType::InputComponentType);
        auto kbs = pInput->GetKeyboardState();
        auto ms = pInput->GetMouseState();
        auto pWalk = (WalkComponent*)pEntity->GetComponent(ComponentType::WalkComponentType);

        if (ms.leftButton)
        {
            Vector3 delta = Vector3(float(ms.x), float(ms.y), 0.f);
            pTransform->Rotate(Vector3(delta.y, delta.x, 0.) * deltaTime * pWalk->m_rotationGain);
        }

        Vector3 fwd = pTransform->GetForward() * deltaTime * pWalk->m_movementGain;
        Vector3 right = pTransform->GetRight() * deltaTime * pWalk->m_movementGain;

        if (kbs.W)
            pTransform->Move(fwd);
        if (kbs.S)
            pTransform->Move(-fwd);
        if (kbs.A)
            pTransform->Move(-right);
        if (kbs.D)
            pTransform->Move(right);
        /*if (kbs.D1)
            pEntity->SetTransform(cameraTransform1);
        else if (kbs.D2)
            pEntity->SetTransform(cameraTransform2);*/
    }));
      
       

    Entity* cameraEntity = new Entity("camera");
    auto cameraTransform = new TransformComponent(1, 0, -1, 0, 0, 0);
    auto cameraInputComponent = new InputComponent();
    auto cameraWalkComponent = new WalkComponent(0.003, 0.004);
    auto cameraComponent = new CameraComponent(true);

    cameraEntity->SetTransform(cameraTransform);
    cameraEntity->AddComponent(ComponentType::InputComponentType, cameraInputComponent);
    cameraEntity->AddComponent(ComponentType::WalkComponentType, cameraWalkComponent);
    cameraEntity->AddComponent(ComponentType::CameraComponentType, cameraComponent);

    scene->AddEntity(cameraEntity);
    scene->SetCamera(cameraEntity);



    auto bitmap = new BitmapComponent(1, 1, asphaltTexture, false);
    Entity* e1 = new Entity();
    auto transform1 = new TransformComponent(0, 0, 1, 0, 0, 0, 0.3, 0.3, 0.3);
    e1->SetTransform(transform1);
    e1->AddComponent(ComponentType::BitmapComponentType, bitmap);
    scene->AddEntity(e1);

    auto transform2 = new TransformComponent(0, 0.3, 2, 0, 0, XM_PI/4, 0.3, 0.3, 0.3);
    Entity* e2 = new Entity();
    e2->SetTransform(transform2);
    e2->AddComponent(ComponentType::BitmapComponentType, bitmap);
    scene->AddEntity(e2);

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