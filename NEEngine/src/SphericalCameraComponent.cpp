#include "pch.h"
#include "SphericalCameraComponent.h"

#include "SphericalMath.h"

using namespace DirectX::SimpleMath;

const DirectX::XMMATRIX& SphericalCameraComponent::GetProj()
{
    // TODO: возвращать эллиптическую матрицу
    return Matrix();
}

void SphericalCameraComponent::RecalculateProj()
{
    ellProj = BananaProjectionMatrix(m_nearPlane);
}
