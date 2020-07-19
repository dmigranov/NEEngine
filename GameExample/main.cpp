//inspired by:
//https://www.3dgep.com/introduction-to-directx-11/#Initialize_DirectX

#include <pch.h>
#include "Game.h"
#include "Scene.h"
#include "Camera.h"

#include "SphericalSphere.h"

#include "ResourceManager.h"
#include "InputInfo.h"


#include "Entity.h"

// Components
#include "ComponentType.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "InputHandlerComponent.h"
#include "FirstPersonCameraInputHandlerComponent.h"
#include "BitmapComponent.h"


// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "BitmapRenderSystem.h"

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

    
    Texture* asphaltTexture = resourceManager->CreateTexture(L"asphalt.dds");


    {
        scene->AddSystem(new InputSystem());
        scene->AddSystem(new BitmapRenderSystem());
    }

    Entity* cameraEntity = new Entity();
    auto cameraTransform = new TransformComponent(0, 0, -1, 0, 0, 0);
    cameraEntity->SetTransform(cameraTransform);
    cameraEntity->AddComponent(ComponentType::InputHandlerComponentType, new FirstPersonCameraInputHandlerComponent());
    scene->SetCamera(cameraEntity);

    Entity* e = new Entity();
    auto transform = new TransformComponent(0, 0, 1, 0, 0, 0, 0.3, 0.3, 0.3);
    e->SetTransform(transform);
    e->AddComponent(ComponentType::InputHandlerComponentType, new InputHandlerComponent([](Entity * pEntity, DWORD deltaTime, InputInfo &input) {
        auto pTransform = pEntity->GetTransform();
        auto kb = input.GetKeyboardState();
        if (kb.Up)
            pTransform->Move(0., 0.01, 0.);
        if (kb.Down)
            pTransform->Move(0., -0.01, 0.);
    }));

    e->AddComponent(ComponentType::BitmapComponentType, new BitmapComponent(1, 1, asphaltTexture));

    scene->AddEntity(e);

    return game.StartGame();

}
    
    /*{
        game.MoveCamera(Vector3(0, 0, -XM_PI / 4));
        game.SetCameraFovY(XM_PI / 2);
        game.SetBackgroundColor(DirectX::Colors::PowderBlue);

        auto earthTexture = game.CreateTexture(L"earth.dds");
        auto asteroidTexture = game.CreateTexture(L"asteroid2.dds");
        auto fabricTexture = game.CreateTexture(L"fabric.dds");
        auto sviborgTexture = game.CreateTexture(L"sviborg.dds");
        auto fireTexture = game.CreateTexture(L"fire.dds");
        auto moonTexture = game.CreateTexture(L"moon.dds");
        if (!earthTexture || !moonTexture || !asteroidTexture || !fireTexture || !sviborgTexture || !fabricTexture)
        {
            MessageBox(nullptr, TEXT("Failed to load textures."), TEXT("Error"), MB_OK);
            return 1;
        }

        auto mesh1 = new SphericalSphere(0.15f, 20, 20, earthTexture);
        //auto mesh1 = new SphericalEllipsoid(0.9999f, 0.55f, 0.45f, 40, 40, asteroidTexture);

        mesh1->AddUpdater(Mesh::MeshUpdater([&game](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();
            float gain = 0.045f;
            Matrix m = Matrix::Identity;
            if (ks.U)
                m = SphericalRotationYW(-gain);
            if (ks.J)
                m = SphericalRotationYW(gain);
            if (ks.H)
                m = SphericalRotationXW(gain);
            if (ks.K)
                m = SphericalRotationXW(-gain);
            return  in *  m;  //так всегда вверх!
        }));
        game.AddMesh(mesh1);


        for (int i = 1; i < 8; i++)
        {
            Mesh* mesh = new SphericalSphere(0.15f, 20, 20, earthTexture, SphericalRotationZW(i * XM_PI / 8));
            game.AddMesh(mesh);
        }


        auto moon = new SphericalSphere(0.05f, 20, 20, moonTexture, SphericalRotationZW(-0.39f));
        moon->SetParent(mesh1);
        moon->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            return in * SphericalRotationXZ(delta);
        }));
        game.AddMesh(moon);


        auto asteroid = new SphericalSphere(0.02f, 20, 20, asteroidTexture, SphericalRotationZW(-0.1f));
        asteroid->SetParent(moon);
        asteroid->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            return in * SphericalRotationXZ(7 * delta);
        }));
        game.AddMesh(asteroid);
        
        
        auto head = new SphericalSphere(0.08f, 20, 20, sviborgTexture);
        head->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
            auto ks = Keyboard::Get().GetState();

            static double time = 0;
            if (!ks.Space)
                time += delta;

            return SphericalRotationYW(-0.15f) * SphericalRotationXZ(XM_PI / 2) * SphericalRotationZW(time / 5.) * SphericalRotationYW(0.03 * sin(7 * time));

        }));
        game.AddMesh(head);

        int sect = 8;
        for (int i = 0; i < sect; i++)
        {
            Mesh* mesh = new SphericalSphere(0.01f, 20, 20, fireTexture, SphericalRotationYW(-0.12f) * SphericalRotationYZ(i * XM_2PI / sect));
            mesh->AddUpdater(SphericalMesh::MeshUpdater([i](Matrix in, float delta) {
                return  in * SphericalRotationYZ(delta / 3.f);
            }));
            mesh->SetParent(head);
            game.AddMesh(mesh);
        }
        

        auto mesh2 = SphericalMeshLoader::LoadMesh("mesh3.sph");
        mesh2->SetTexture(fabricTexture);
        mesh2->SetWorldMatrix(SphericalRotationYZ(XM_PIDIV2) * SphericalRotationYW(0.09f));
        game.AddMesh(mesh2);
        
    }*/

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