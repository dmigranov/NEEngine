#include "pch.h"
#include "HyperbolicCameraComponent.h"

const DirectX::XMMATRIX& HyperbolicCameraComponent::GetProj()
{
    return CameraComponent::GetProj(); //the usual, Euclidean, projection matrix can be used in the hyperbolic case
}
