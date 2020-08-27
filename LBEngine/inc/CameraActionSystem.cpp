#include "pch.h"
#include "CameraActionSystem.h"
#include "Entity.h"

#include "TransformComponent.h"
#include "InputComponent.h"
#include "WalkComponent.h"
#include "PhysicsComponent.h"

using namespace DirectX::SimpleMath;

/*CameraActionSystem::CameraActionSystem() : ActionSystem({ ComponentType::InputComponentType, ComponentType::TransformComponentType, ComponentType::WalkComponentType, ComponentType::PhysicsComponentType }, [](Entity* pEntity, DWORD deltaTime)  {

    auto pTransform = pEntity->GetTransform();
    auto pInput = pEntity->GetComponent<InputComponent>();
    auto kbs = pInput->GetKeyboardState();
    auto ms = pInput->GetMouseState();
    auto pWalk = (WalkComponent*)pEntity->GetComponent<WalkComponent>();
    auto pVelocity = (PhysicsComponent*)pEntity->GetComponent<PhysicsComponent>();


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



})
{}
*/