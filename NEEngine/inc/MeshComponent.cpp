#include "pch.h"
#include "MeshComponent.h"

MeshComponent::MeshComponent(ID3D11Buffer* g_d3dVertexBuffer, ID3D11Buffer* g_d3dIndexBuffer, Effect* effect)
{
}

Effect* MeshComponent::GetEffect() const
{
    return nullptr;
}

void MeshComponent::SetEffect(Effect* effect)
{
}

MeshComponent::~MeshComponent()
{
    SafeRelease(g_d3dVertexBuffer);
    SafeRelease(g_d3dIndexBuffer);
}
