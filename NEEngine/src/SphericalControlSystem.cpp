#include "pch.h"
#include "SphericalControlSystem.h"

#include "Entity.h"
#include "InputComponent.h"
#include "SphericalTransformComponent.h"

SphericalControlSystem::SphericalControlSystem(double movementSpeed, double rotationSpeed) : ActionSystem([movementSpeed, rotationSpeed](Entity* pEntity, double deltaTime) {

    auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
    auto pInput = pEntity->GetComponent<InputComponent>();
    auto kbs = pInput->GetKeyboardState();
    auto ms = pInput->GetMouseState();

    if (ms.leftButton)
    {
        double dx = ms.x * rotationSpeed * deltaTime, dy = ms.y * rotationSpeed * deltaTime;
    }

    if (kbs.W)
        ;
    if (kbs.S)
        ;
    if (kbs.A)
        ;
    if (kbs.D)
        ;

})
{ }