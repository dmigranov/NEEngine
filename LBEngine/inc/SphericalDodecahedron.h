#pragma once
#include "SphericalMesh.h"
class SphericalDodecahedron :
	public SphericalMesh
{
public:
	enum class FixedCoordinate {
		FC_X,
		FC_Y,
		FC_Z,
		FC_W
	};

	SphericalDodecahedron(double wSec, DirectX::XMMATRIX world);
	SphericalDodecahedron(double wSec);

	void SetSectionHeight(double newSectionHeight);
	double GetSectionHeight();

private:
	FixedCoordinate fc;
	double sectionHeight;
	DirectX::XMFLOAT4 GenerateRandomColor();
};

