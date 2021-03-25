#pragma once
#include "MeshComponent.h"
template <class VertexData>
class SphericalMeshComponent :
    public MeshComponent<VertexData>
{

public:
    SphericalMeshComponent(int nv, VertexData* vertices, int ni, WORD* indices);


};

template<class VertexData>
inline SphericalMeshComponent<VertexData>::SphericalMeshComponent(int nv, VertexData* vertices, int ni, WORD* indices) : MeshComponent<VertexData>(nv, vertices, ni, indices)
{ }