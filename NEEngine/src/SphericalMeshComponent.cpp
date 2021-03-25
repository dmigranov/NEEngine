#include "pch.h"
#include "SphericalMeshComponent.h"

SphericalMeshComponent::SphericalMeshComponent(int nv, VertexPosTex* vertices, int ni, WORD* indices) : MeshComponent(nv, vertices, ni, indices)
{
	const UINT vertexStride = sizeof(VertexPosTex);   //Each stride is the size (in bytes) of the elements that are to be used from that vertex buffer.
	const UINT offset = 0;
	//todo: реализовать конструктор
}
