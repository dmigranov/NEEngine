#include "pch.h"
#include "SphericalCameraComponent.h"

#include "SphericalMath.h"

using namespace DirectX::SimpleMath;

const DirectX::XMMATRIX& SphericalCameraComponent::GetProj()
{
    // TODO: возвращать эллиптическую матрицу
    return Matrix();
}

const DirectX::XMMATRIX& SphericalCameraComponent::GetFrontSphericalProj() const
{
    if (m_shouldRecalc)
        RecalculateProj();
    return m_frontProj;
}

void SphericalCameraComponent::RecalculateProj()
{
    //todo? float aspect = (float)((sw * vw) / (sh * vh)); 
    m_ellProj = BananaProjectionMatrix(m_fovY, m_aspect, m_nearPlane);
    m_frontProj = BananaProjectionMatrixFrontHalf(m_fovY, m_aspect, m_nearPlane);
    m_backProj = BananaProjectionMatrixBackHalf(m_fovY, m_aspect, m_nearPlane);

    m_shouldRecalc = false;
}
