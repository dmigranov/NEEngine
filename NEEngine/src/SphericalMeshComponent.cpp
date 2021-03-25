#include "pch.h"
#include "SphericalMeshComponent.h"

#include "Game.h"


SphericalMeshComponent::SphericalMeshComponent(int nv, VertexPosTex* vertices, int ni, WORD* indices) : VertexTexMeshComponent(nv, vertices, ni, indices)
{ }
