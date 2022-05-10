#include "pch.h"
#include "ToricControlSystem.h"
#include "Entity.h"

#include "ToricTransformComponent.h"
#include "InputComponent.h"
#include "CameraComponent.h"

using namespace DirectX::SimpleMath;


ToricControlSystem::ToricControlSystem(double movementSpeed, double rotationSpeed) : ActionSystem([movementSpeed, rotationSpeed, this](Entity* pEntity, double deltaTime) {
    auto pTransform = pEntity->GetComponent<ToricTransformComponent>();
    auto pInput = pEntity->GetComponent<InputComponent>();
    auto kbs = pInput->GetKeyboardState();
    auto ms = pInput->GetMouseState();

    //todo: speeds

    if (pInput->IsRelative())
    {
        Vector3 delta = Vector3(float(ms.x), float(ms.y), 0.f);
        pTransform->Rotate(Vector3(delta.y, delta.x, 0.) * deltaTime * 1.9);
    }

    Vector3 fwd = pTransform->GetForward() * deltaTime * 10;
    Vector3 right = pTransform->GetRight() * deltaTime * 10;

    if (kbs.LeftShift || kbs.RightShift)
    {
        fwd *= 5;
        right *= 5;
    }

    if (kbs.W)
        pTransform->Move(fwd);
    if (kbs.S)
        pTransform->Move(-fwd);
    if (kbs.A)
        pTransform->Move(-right);
    if (kbs.D)
        pTransform->Move(right);

    pInput->SetRelative(ms.leftButton ? true : false);
    }) {}