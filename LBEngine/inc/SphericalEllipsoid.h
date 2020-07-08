#pragma once
#include "SphericalMesh.h"
class SphericalEllipsoid :
	public SphericalMesh
{
public:
	SphericalEllipsoid(float a, float b, float c, int sliceCount, int stackCount, Texture* texture);
	SphericalEllipsoid(float a, float b, float c, int sliceCount, int stackCount, Texture* texture, DirectX::XMMATRIX world);
};

