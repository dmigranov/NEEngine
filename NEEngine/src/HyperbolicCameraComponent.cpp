#include "pch.h"
#include "HyperbolicCameraComponent.h"

HyperbolicCameraComponent::HyperbolicCameraComponent()
{
    m_shouldRecalc = true;
}

const DirectX::XMMATRIX& HyperbolicCameraComponent::GetProj()
{
    return CameraComponent::GetProj(); //the usual, Euclidean, projection matrix can be used in the hyperbolic case
}
