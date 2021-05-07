#include "pch.h"
#include "SphericalControlSystem.h"

#include "Entity.h"
#include "InputComponent.h"
#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"

#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SphericalControlSystem::SphericalControlSystem(double movementSpeed, double rotationSpeed) : ActionSystem([movementSpeed, rotationSpeed](Entity* pEntity, double deltaTime) {

    auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
    auto pInput = pEntity->GetComponent<InputComponent>();
    auto kbs = pInput->GetKeyboardState();
    auto ms = pInput->GetMouseState();

    //todo: переделать так, чтобы использовался метод Move Transform'а, а не вручную сформированыне матрицы

    double m_dx = 0, m_dy = 0;

    if (ms.leftButton)
    {
        m_dx = ms.x * rotationSpeed * deltaTime;
        m_dy = ms.y * rotationSpeed * deltaTime;
    }
     


    if (kbs.W)
        ;
    if (kbs.S)
        ;
    if (kbs.A)
        ;
    if (kbs.D)
        ;

    Matrix dT = SphericalRotationXW(-dx) * SphericalRotationYW(-dy) * SphericalRotationZW(-dz);


})
{ }