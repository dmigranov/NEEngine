#include "pch.h"
#include "SphericalCameraComponent.h"

using namespace DirectX::SimpleMath;

const DirectX::XMMATRIX& SphericalCameraComponent::GetProj()
{
    // TODO: возвращать эллиптическую матрицу
    return Matrix();
}

void SphericalCameraComponent::RecalculateProj()
{
}
