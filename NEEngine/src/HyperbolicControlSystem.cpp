#include "pch.h"
#include "HyperbolicControlSystem.h"

#include "Entity.h"
#include "InputComponent.h"
#include "HyperbolicTransformComponent.h"
#include "HyperbolicCameraComponent.h"

#include "HyperbolicMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

HyperbolicControlSystem::HyperbolicControlSystem(double movementSpeed, double rotationSpeed) : ActionSystem([movementSpeed, rotationSpeed, this](Entity* pEntity, double deltaTime) {
    auto pTransform = pEntity->GetComponent<HyperbolicTransformComponent>();
    auto pInput = pEntity->GetComponent<InputComponent>();
    auto kbs = pInput->GetKeyboardState();
    auto ms = pInput->GetMouseState();

    double m_dx = 0, m_dy = 0;

    if (pInput->IsRelative())
    {
        //pitch - around x, yaw - around y
        m_dx = -ms.x * rotationSpeed * deltaTime;
        m_dy = ms.y * rotationSpeed * deltaTime;

        m_pitch += m_dy;
        m_yaw += m_dx;

        m_pitch = std::max<double>(-m_pitchLimit, m_pitch);
        m_pitch = std::min<double>(+m_pitchLimit, m_pitch);

        // keep longitude in sane range by wrapping
        if (m_yaw > DirectX::XM_PI)
            m_yaw -= DirectX::XM_2PI;
        else if (m_yaw < -DirectX::XM_PI)
            m_yaw += DirectX::XM_2PI;

        // OLD CODE BEGIN
        RYaw = HyperbolicRotationXZ(-m_yaw);
        RPitch = HyperbolicRotationYZ(-m_pitch);
        R = RPitch * RYaw;
        // OLD CODE END

        pTransform->SetPitchYawRoll(m_pitch, m_yaw, 0);
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

    if (dx != 0 || dz != 0)
    {
        Vector4 tempVector(-dx, 0, -dz, 0);
        tempVector = Vector4::Transform(tempVector, RYaw);

        pTransform->Move(tempVector.x, tempVector.y, tempVector.z);
    }

    pInput->SetRelative(ms.leftButton ? true : false);
    })
{ }