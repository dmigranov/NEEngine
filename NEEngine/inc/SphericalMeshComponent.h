#pragma once
#include "VertexTexMeshComponent.h"
class SphericalMeshComponent :
    public VertexTexMeshComponent
{
    friend class SphericalRenderSystem;

public:
    SphericalMeshComponent(int nv, VertexPosTex* vertices, int ni, WORD* indices);


};

