#include "pch.h"
#include "FirstPersonCameraInputHandlerComponent.h"

#include "Entity.h"
#include "TransformComponent.h"
#include "InputInfo.h"

using namespace DirectX::SimpleMath;

FirstPersonCameraInputHandlerComponent::FirstPersonCameraInputHandlerComponent() :
    InputHandlerComponent([](Entity* pEntity, DWORD deltaTime, InputInfo& input) {
    //todo: по готовности камеры вынести в отдельный InputHandlerComponent и включить в библиотеку
    //todo: перенести в поля 
    static const double MOVEMENT_GAIN = 0.003;
    static const double ROTATION_GAIN = 0.004;

    auto pTransform = pEntity->GetTransform();
    auto kbs = input.GetKeyboardState();
    auto ms = input.GetMouseState();

    if (ms.leftButton)
    {
        Vector3 delta = Vector3(float(ms.x), float(ms.y), 0.f);
        pTransform->Rotate(Vector3(delta.y, delta.x, 0.) * deltaTime * ROTATION_GAIN);
    }

    Vector3 fwd = pTransform->GetForward() * deltaTime * MOVEMENT_GAIN;
    Vector3 right = pTransform->GetRight() * deltaTime * MOVEMENT_GAIN;

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
