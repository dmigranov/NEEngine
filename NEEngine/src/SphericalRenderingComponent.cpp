#include "pch.h"
#include "SphericalRenderingComponent.h"

SphericalVisibility SphericalRenderingComponent::GetSphericalVisibility()
{
    return m_sphericalVisibility;
}

void SphericalRenderingComponent::SetSphericalVisibility(SphericalVisibility sphVisibility)
{
    m_sphericalVisibility = sphVisibility;
}
