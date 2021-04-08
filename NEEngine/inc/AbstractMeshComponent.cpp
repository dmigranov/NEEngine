#include "pch.h"
#include "AbstractMeshComponent.h"


Effect* AbstractMeshComponent::GetEffect() const
{
    return m_pEffect;
}

void AbstractMeshComponent::SetEffect(Effect * effect)
{
    m_pEffect = effect;
}
