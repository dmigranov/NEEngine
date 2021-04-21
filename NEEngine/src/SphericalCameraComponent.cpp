#include "pch.h"
#include "SphericalCameraComponent.h"

#include "SphericalMath.h"

using namespace DirectX::SimpleMath;

const DirectX::XMMATRIX& SphericalCameraComponent::GetProj()
{
    return GetEllipticProj();
}

const DirectX::XMMATRIX& SphericalCameraComponent::GetFrontSphericalProj() 
{
    if (m_shouldRecalc)
        RecalculateProj();
    return m_frontProj;
}

const DirectX::XMMATRIX& SphericalCameraComponent::GetBackSphericalProj()
{
    if (m_shouldRecalc)
        RecalculateProj();
    return m_backProj;
}

const DirectX::XMMATRIX& SphericalCameraComponent::GetEllipticProj()
{
    if (m_shouldRecalc)
        RecalculateProj();
    return m_ellProj;
}

void SphericalCameraComponent::RecalculateProj()
{
    //todo? float aspect = (float)((sw * vw) / (sh * vh)); 
    m_ellProj = BananaProjectionMatrix(m_fovY, m_aspect, m_nearPlane);
    m_frontProj = BananaProjectionMatrixFrontHalf(m_fovY, m_aspect, m_nearPlane);
    m_backProj = BananaProjectionMatrixBackHalf(m_fovY, m_aspect, m_nearPlane);

    m_shouldRecalc = false;
}
