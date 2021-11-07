#pragma once

#include "Geometries/SphericalEllipticGeometry.h"
#include "WalkComponent.h"
#include "InputSystem.h"
#include "RandomSphericalGenerator.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//xyzw
Vector3 GetSphericalFromCartesian(float x4, float x3, float x2, float x1) //в рассчёте что радиус 1
{
    float x42 = x4 * x4;
    float x22 = x2 * x2;
    float x32 = x3 * x3;

    float a1 = acosf(x1);
    if (x2 == 0 && x3 == 0 && x4 == 0)
        if (x1 > 0)
            return Vector3(a1, 0, 0);
        else
            return Vector3(a1, XM_PI, XM_PI);

    float a2 = acosf(x2 / sqrtf(x22 + x32 + x42));
    if (x3 == 0 && x4 == 0)
        if (x2 > 0)
            return Vector3(a1, a2, 0);
        else
            return Vector3(a1, a2, XM_PI);

    float a3;
    if (x4 >= 0)
        a3 = acosf(x3 / sqrtf(x32 + x42));
    else
        a3 = XM_2PI - acosf(x3 / sqrtf(x32 + x42));

    return Vector3(a1, a2, a3);
}

int main(int argc, char* argv[])
{
    double radius = 1.;

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

        //transfcomp и meshcom зарегистр по умолчанию... 

        componentTypeManager->SetTypeAdditionEnded();
    }

    Texture* earthTexture = resourceManager->CreateTexture(L"earth8k.dds");

    auto renderSystem = new SphericalRenderSystem();
    renderSystem->SetRadius(radius);
    scene->AddSystem(new InputSystem());
    scene->AddSystem(renderSystem);
    scene->AddSystem(new SphericalControlSystem(0.3, 1.3));
    /*
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


            if (kbs.R)
                pTransform->Move(up);
            if (kbs.F)
                pTransform->Move(-up);

            if (kbs.T)
                pTransform->Rotate(deltaTime, 0, 0);
            if (kbs.G)
                pTransform->Rotate(0, deltaTime, 0);
            if (kbs.B)
                pTransform->Rotate(0, 0, deltaTime);
        }));
        */

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

    auto entity1 = new Entity(), entity2 = new Entity();

    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(0.1, 20, 20);
    smc->SetEffect(effect);

    /*
    cameraComponent->SetFovY(XM_PI/2 - 0.2); //эксперимент с видимостью
    int sphereCount = 6;
    for (int i = 1; i < sphereCount; i++)
    {
        auto transformComponent = new SphericalTransformComponent(0, i * XM_PI / sphereCount, 0);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);
        scene->AddEntity(entity);
    }
    for (int i = 1; i < sphereCount; i++)
    {
        auto transformComponent = new SphericalTransformComponent(0, 0, i * XM_PI / sphereCount);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);
        scene->AddEntity(entity);
    }
    */

    //равномерное распределение
   
    RandomSphericalGenerator generator(radius);
    int sphereCount = 3;
    for (int i = 0; i < sphereCount; i++)
    {
        auto point = generator.GeneratePoint();
        //std::cout << point.x << " " << point.y << " " << point.z << " " << point.w << std::endl;
        auto point_sph = GetSphericalFromCartesian(point.x, point.y, point.z, point.w);
        //std::cout << point_sph.x << " " << point_sph.y << " " << point_sph.z << std::endl;
        auto transformComponent = new SphericalTransformComponent(point_sph.y, point_sph.x, point_sph.z);
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<MeshComponent>(smc);
        scene->AddEntity(entity);

        //if(пересекаются сферы с уже добавленными)
            //переген.
    }

    double x = -0.855854, y = 0.224945, z = -0.464042, w = 0.0397378;
    auto transformComponent = new SphericalTransformComponent();
    //первые три к-ты - как бы независимы
    //transformComponent->Move(0, asin(y), 0);
    transformComponent->MoveAbsolute(x, y, z, w);
    auto pos = transformComponent->GetSphericalPosition();
    std::cout << pos.x << " " << pos.y << " " << pos.z << " " << pos.w << std::endl;

    transformComponent->Move(XM_PI, 0, 0);
    pos = transformComponent->GetSphericalPosition();
    std::cout << pos.x << " " << pos.y << " " << pos.z << " " << pos.w << std::endl;

    scene->AddSystem(new ActionSystem<InputComponent>(
        [effect, renderSystem](Entity* pEntity, double deltaTime) {
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();

            if (kbs.D1)
                effect->SetMode(true);
            else if (kbs.D2)
                effect->SetMode(false);

            if (kbs.I)
                renderSystem->SetRadius(renderSystem->GetRadius() + 0.1);
            else if (kbs.O)
            {
                auto radius = renderSystem->GetRadius();
                if (radius > 0.1)
                    renderSystem->SetRadius(radius -0.1);
            }
                
        }));


    return game.StartGame();
} 
