#include "pch.h"
#include "FirstPersonCameraInputHandlerComponent.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "InputInfo.h"

using namespace DirectX::SimpleMath;

FirstPersonCameraInputHandlerComponent::FirstPersonCameraInputHandlerComponent() :
    InputHandlerComponent([this](Entity* pEntity, DWORD deltaTime, InputInfo& input) {
    auto pTransform = pEntity->GetTransform();
    auto kbs = input.GetKeyboardState();
    auto ms = input.GetMouseState();

    if (ms.leftButton)
    {
        Vector3 delta = Vector3(float(ms.x), float(ms.y), 0.f);
        pTransform->Rotate(Vector3(delta.y, delta.x, 0.) * deltaTime * m_rotationGain);
    }

    Vector3 fwd = pTransform->GetForward() * deltaTime * m_movementGain;
    Vector3 right = pTransform->GetRight() * deltaTime * m_movementGain;

    if (kbs.W)
        pTransform->Move(fwd);
    if (kbs.S)
        pTransform->Move(-fwd);
    if (kbs.A)
        pTransform->Move(-right);
    if (kbs.D)
        pTransform->Move(right);
})
{
    ;
}
