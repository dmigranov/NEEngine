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
        //pitch - around x, yaw - around y
        m_dx = ms.x * rotationSpeed * deltaTime;
        m_dy = ms.y * rotationSpeed * deltaTime;

        m_pitch += m_dx;
        m_yaw += m_dy;

        m_pitch = std::max<double>(-m_pitchLimit, m_pitch);
        m_pitch = std::min<double>(+m_pitchLimit, m_pitch);

        // keep longitude in sane range by wrapping
        if (m_yaw > DirectX::XM_PI)
            m_yaw -= DirectX::XM_2PI;
        else if (m_yaw < -DirectX::XM_PI)
            m_yaw += DirectX::XM_2PI;
    }
     
    double dx = 0, dy = 0, dz = 0;

    if (kbs.W)
        dz = movementSpeed * deltaTime;
    if (kbs.S)
        dz = -movementSpeed * deltaTime;
    if (kbs.A)
        dx = -movementSpeed * deltaTime;
    if (kbs.D)
        dx = movementSpeed * deltaTime;

    Matrix dT =  SphericalRotationZW(dz) * SphericalRotationXW(dx);

    //T = T * RYaw * dT * RYaw.Transpose();	//матрица T^1 для вычисления view = T^-1 * R^-1
    T = RYaw.Transpose() * dT * RYaw * T;
    auto transformMatrix = R * T;

    pTransform->SetWorld(transformMatrix);

})
{ }