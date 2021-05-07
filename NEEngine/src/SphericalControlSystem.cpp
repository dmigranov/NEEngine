#include "pch.h"
#include "SphericalControlSystem.h"

#include "Entity.h"
#include "InputComponent.h"
#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"

#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SphericalControlSystem::SphericalControlSystem(double movementSpeed, double rotationSpeed) : ActionSystem([movementSpeed, rotationSpeed, this](Entity* pEntity, double deltaTime) {

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
     
    double dx = 0, dy = 0, dz = 0;

    if (kbs.W)
        dz = movementSpeed * deltaTime;
    if (kbs.S)
        dz = -movementSpeed * deltaTime;
    if (kbs.A)
        dx = movementSpeed * deltaTime;
    if (kbs.D)
        dx = -movementSpeed * deltaTime;

    Matrix dT = SphericalRotationXW(-dx) * SphericalRotationYW(-dy) * SphericalRotationZW(-dz);

    T = T * RYaw * dT * RYaw.Transpose();	//движение в одной плоскости

    m_view = T * R;

})
{ }