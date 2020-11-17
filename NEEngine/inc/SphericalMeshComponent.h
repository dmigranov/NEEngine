#pragma once
#include "MeshComponent.h"
class SphericalMeshComponent :
    public MeshComponent
{
    friend class SphericalRenderSystem;

public:
    SphericalMeshComponent(int nv, VertexPosTex* vertices, int ni, WORD* indices);


};

