#include "pch.h"
#include "CameraActionSystem.h"
#include "Entity.h"

#include "TransformComponent.h"
#include "InputComponent.h"
#include "WalkComponent.h"
#include "PhysicsComponent.h"

using namespace DirectX::SimpleMath;

CameraActionSystem::CameraActionSystem() : ActionSystem([](Entity* pEntity, double deltaTime)  {

    auto pTransform = pEntity->GetTransform();
    auto pInput = pEntity->GetComponent<InputComponent>();
    auto kbs = pInput->GetKeyboardState();
    auto ms = pInput->GetMouseState();

    if (ms.leftButton)
    {
        Vector3 delta = Vector3(float(ms.x), float(ms.y), 0.f);
        pTransform->Rotate(Vector3(delta.y, delta.x, 0.) * deltaTime * 0.3);
    }

    Vector3 fwd = pTransform->GetForward() * deltaTime * 4;
    Vector3 right = pTransform->GetRight() * deltaTime * 4;

    if (kbs.W)
        pTransform->Move(fwd);
    if (kbs.S)
        pTransform->Move(-fwd);
    if (kbs.A)
        pTransform->Move(-right);
    if (kbs.D)
        pTransform->Move(right);

})
{}
