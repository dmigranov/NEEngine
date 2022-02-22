#pragma once

#include "main.h"

#include "InputSystem.h"
#include "TextPrintingSystem.h"
#include "TextComponent.h"
#include "DopplerComponent.h"
#include "RandomSphericalGenerator.h"
#include "SphericalMath.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

int main(int argc, char* argv[])
{
    double radius = 1.;

    Game& game = Game::GetInstance();
    game.InitializeEngine(L"Test game", true, false, true);
    game.SetBackgroundColor(DirectX::Colors::Black);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager();

    {
        auto componentTypeManager = game.GetComponentTypeManager();
        componentTypeManager->RegisterComponentType<CameraComponent>();
        componentTypeManager->RegisterComponentType<InputComponent>();

        componentTypeManager->RegisterComponentType<SphericalTransformComponent>();
        componentTypeManager->RegisterComponentType<SphericalCameraComponent>();
        componentTypeManager->RegisterComponentType<SphericalRenderingComponent>();

        componentTypeManager->RegisterComponentType<TextComponent>();

        componentTypeManager->RegisterComponentType<DopplerComponent>();

        componentTypeManager->RegisterComponentType<UpdaterComponent>();

        componentTypeManager->SetTypeAdditionEnded();         //MeshComponent - registered by default
    }

    auto friedmannHwnd = CreateFriedmannWindow();

    Texture* earthTexture = resourceManager->CreateTexture(L"earth8k.dds");
    Texture* rainbowTexture1 = resourceManager->CreateTexture(L"rainbow4_rot.dds");
    Texture* rainbowTexture2 = resourceManager->CreateTexture(L"rainbow4.dds");
    Texture* greenTexture = resourceManager->CreateTexture(L"green_texture.dds");

    auto renderSystem = new SphericalRenderSystem();
    renderSystem->SetRadius(radius);
    scene->AddSystem(new InputSystem());
    scene->AddSystem(renderSystem);
    scene->AddSystem(new SphericalControlSystem(0.3, 1.3));
    scene->AddSystem(new UpdaterSystem());


    Entity* cameraEntity = new Entity("camera1");
    auto cameraTransform = new SphericalTransformComponent();
    auto cameraComponent = new SphericalCameraComponent();
    cameraComponent->SetFovY(XM_PI / 3);
    cameraEntity->AddComponent<SphericalTransformComponent>(cameraTransform);
    cameraEntity->AddComponent<SphericalCameraComponent>(cameraComponent);
    cameraEntity->AddComponent<InputComponent>(new InputComponent());
    scene->SetCamera(cameraEntity, cameraComponent);
    scene->AddEntity(cameraEntity);

    auto effect = new SphericalDopplerEffect(rainbowTexture2, 0.1, DirectX::Colors::Black);
    //auto effectEarth = new SphericalDopplerEffect(greenTexture, 0.1, DirectX::Colors::Black);
    //auto effect = new SphericalExpFogEffect(earthTexture, 0.15, DirectX::Colors::Black);

    auto pointEffect = new SphericalExpFogPointEffect(0.1, DirectX::Colors::Black);

    double objectRadius = 0.1;
    auto smc = SphericalMeshComponentFactory::CreateSphericalSphere(objectRadius, 30, 30);
    smc->SetEffect(effect);

    //auto earth_mc = SphericalMeshComponentFactory::CreateSphericalSphere(objectRadius, 30, 30);
    //earth_mc->SetEffect(effectEarth);

    auto pointComp = SphericalMeshComponentFactory::CreateSphericalPoint();
    pointComp->SetEffect(pointEffect);

    // --- Uniform Distribution --- //

    RandomSphericalGenerator generator(radius);
    int sphereCount = 1;
    auto randomPoints = new Vector4[sphereCount];
    auto entities = new Entity * [sphereCount];
    for (int i = 0; i < sphereCount; i++)
    {
    again:
        auto point = generator.GeneratePoint();

        for (int j = 0; j < i; j++)
        {
            auto otherPoint = randomPoints[j];
            auto distance = SphericalDistance(point, otherPoint, radius);

            if (distance < 2 * objectRadius)
                goto again;
        }

        randomPoints[i] = point;
        auto transformComponent = new SphericalTransformComponent();
        //transformComponent->MoveAbsolute(point.x, point.y, point.z, point.w);

        auto sphericalRenderingComponent = new SphericalRenderingComponent();
        auto dopplerComponent = new DopplerComponent();
        auto entity = new Entity();
        entity->AddComponent<SphericalTransformComponent>(transformComponent);
        entity->AddComponent<SphericalRenderingComponent>(sphericalRenderingComponent);
        entity->AddComponent<DopplerComponent>(dopplerComponent);
        entity->AddComponent<MeshComponent>(smc);
        //entity->AddComponent<MeshComponent>(pointComp);

        scene->AddEntity(entity);
        entities[i] = entity;
    }

    delete[] randomPoints;

    scene->AddSystem(new TextPrintingSystem());
    auto textEntity1 = new Entity();
    textEntity1->AddComponent<TextComponent>(new TextComponent([cameraTransform, renderSystem](double delta) {
        auto pos = cameraTransform->GetSphericalPosition();
        auto x = pos.x, y = pos.y, z = pos.z, w = pos.w;
        std::stringstream ss;

        ss << std::fixed << std::setprecision(2);
        ss << "X: " << pos.x << std::endl;
        ss << "Y: " << pos.y << std::endl;
        ss << "Z: " << pos.z << std::endl;
        ss << "W: " << pos.w << std::endl;
        ss << "R: " << renderSystem->GetRadius() << std::endl;

        return ss.str();

        }, 10, 10, Alignment::UpLeft, DirectX::Colors::White));

    scene->AddEntity(textEntity1);
    
    int currentSphereNumber = -1;

    auto textEntity2 = new Entity();
    textEntity2->AddComponent<TextComponent>(new TextComponent([&currentSphereNumber](double delta) {
        
        std::stringstream ss;

        ss << std::fixed << std::setprecision(2);
        if(currentSphereNumber >= 0)
            ss << "Sphere " << currentSphereNumber << std::endl;

        return ss.str();

        }, 10, 10, Alignment::DownRight, DirectX::Colors::White));

    scene->AddEntity(textEntity2);

    System* controlSystem = nullptr;
    System* visibilitySystem = nullptr;
    System* radiusUpdateSystem = nullptr;
    System* animationSystem = nullptr;

    auto timer = CreateFriedmannSystems(effect, cameraTransform, renderSystem, &controlSystem, &visibilitySystem, &radiusUpdateSystem, &animationSystem);
    
    scene->AddSystem(controlSystem);
    scene->AddSystem(visibilitySystem);
    scene->AddSystem(animationSystem);

    scene->AddSystem(radiusUpdateSystem);   // !!! has to be after all systems where simulation time changes!

    scene->AddSystem(new ActionSystem<InputComponent>(
        [entities, sphereCount, cameraTransform, objectRadius,
        &currentSphereNumber, cameraComponent, timer, &game]
    (Entity* pEntity, double deltaTime) {
            auto pInput = pEntity->GetComponent<InputComponent>();
            auto kbs = pInput->GetKeyboardState();
            auto ms = pInput->GetMouseState();

            double radius = SphericalEffect::GetRadius();
            auto cameraPos = cameraTransform->GetSphericalPosition();

            //radius of spheres in the Euclidean space, after projection
            auto w_sphere = radius - 2 * radius * pow(sin(objectRadius / radius / 2), 2);
            auto r_sphere = sqrt(radius * radius - w_sphere * w_sphere);
            auto r_projected = r_sphere / w_sphere;
            auto r_projected_sq = r_projected * r_projected;

            // todo: идея: при проецировании использовать вместо view - произведение view на матрицу, 
            // передвигающую её (прямо - просто движение по z) к объекту
            // это решит проблему нулевого w 

            // todo: идея: также цикл по всем объектам (можно отбросить все с отрицательным z
            // после применения view, а может, не надо - копии тоже можно выбирать)
            // осуществляем проецирование, и проверяем близость центра до координат выбранной 
            // курсором точки. Единственная проблема - подсчитать нужный радиус проецирования


            Vector3 rayStart(0.f, 0.f, 0.f);    // position - always (0, 0, 0)
            Vector3 direction(0.f, 0.f, 1.f);   // direction - always (0, 0, 1)

            float minDist = 100000.;
            int minIndex = -1;

            const auto& view = cameraTransform->GetView();
            const Matrix& proj = cameraComponent->GetProj();

            int width, height;
            game.GetWindowSize(width, height);

            for (int i = 0; i < sphereCount; i++)
            {
                Entity* sphere = entities[i];
                auto pTransform = sphere->GetComponent<SphericalTransformComponent>();
                const auto& world = pTransform->GetWorld();
                auto sphericalPosition = pTransform->GetSphericalPosition();


                Vector4 testVector1(0, r_sphere, 0, w_sphere);
                Vector4 viewVector1 = Vector4::Transform(Vector4::Transform(testVector1, world), view);
                Vector4 viewVector2 = Vector4::Transform(sphericalPosition, view);
                Vector4 resVector1 = Vector4::Transform(viewVector1, proj);
                Vector4 resVector2 = Vector4::Transform(viewVector2, proj);
                if (resVector1.w == 0 || resVector2.w == 0)
                    continue;
                    
                resVector1 /= resVector1.w;
                resVector2 /= resVector2.w;

                if (ms.leftButton && !pInput->IsRelative())
                {
                    //std::cout << resVector1.x << " " << resVector1.y << " " << resVector1.z << std::endl;
                    //std::cout << resVector2.x << " " << resVector2.y << " " << resVector2.z << std::endl;
                    //double distance_sq = pow(resVector1.x - resVector2.x, 2) + pow(resVector1.y - resVector2.y, 2) ;
                    //std::cout << distance_sq << std::endl;
                    //std::cout << r_projected_sq << std::endl;
                }
                double distance_sq = pow(resVector1.x - resVector2.x, 2) + pow(resVector1.y - resVector2.y, 2);



                //double t = RayTraceSpherePos(sphericalPosition, rayStart, direction, view, proj, distance_sq);
                
                if (pInput->IsRelative())
                    continue;



                if (ms.leftButton && !pInput->IsRelative()) //debug
                {
                    std::cout << ms.x << " " << ms.y << std::endl;
                    double mouseX = (double)ms.x / width;
                    double mouseY = (double)ms.y / height; // это - от 0 до 1
                    std::cout << mouseX << " " << mouseY << std::endl;

                    double t = RayTraceSphereMouse(mouseX, mouseY, sphericalPosition, view, proj, distance_sq);

                    if (t < 0)
                    {
                        continue;
                        //t = RayTraceSphereNeg(sphericalPosition, rayStart, direction, view, r_projected_sq);
                        //if (t < 0)
                        //    continue; //todo: чтобы во всех четвертях работало
                    }

                    if (t < minDist) {
                        minDist = t;
                        minIndex = i;
                    }
                }

            }

            currentSphereNumber = minIndex;
            if (minIndex >= 0)
            {
                auto selectedEntity = entities[currentSphereNumber];
                auto dopplerComponent = selectedEntity->GetComponent <DopplerComponent>();
                if (ms.rightButton)
                    dopplerComponent->SetSelected(true);
                else if (kbs.Space)
                    dopplerComponent->SetSelected(false);
            }



        }));

    return game.StartGame();
}