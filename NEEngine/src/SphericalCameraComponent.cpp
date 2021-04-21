#include "pch.h"
#include "SphericalCameraComponent.h"

#include "SphericalMath.h"

using namespace DirectX::SimpleMath;

const DirectX::XMMATRIX& SphericalCameraComponent::GetProj()
{
    // TODO: ���������� ������������� �������
    return Matrix();
}

void SphericalCameraComponent::RecalculateProj()
{
    //todo? float aspect = (float)((sw * vw) / (sh * vh)); 
    ellProj = BananaProjectionMatrix(m_fovY, m_aspect, m_nearPlane);
    frontProj = BananaProjectionMatrixFrontHalf(m_fovY, m_aspect, m_nearPlane);
    backProj = BananaProjectionMatrixBackHalf(m_fovY, m_aspect, m_nearPlane);

    m_shouldRecalc = false;
}
