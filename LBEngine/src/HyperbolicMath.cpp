#include "pch.h"
#include "HyperbolicMath.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

Matrix HyperbolicRotationZW(float d)
{
	return Matrix(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, coshf(d), sinhf(d),
		0.f, 0.f, -sinhf(d), coshf(d));
}

Matrix HyperbolicRotationXW(float d)
{
	return Matrix(coshf(d), 0.f, 0.f, sinhf(d),
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		-sinhf(d), 0.f, 0.f, coshf(d));
}

Matrix HyperbolicRotationYW(float d)
{
	return Matrix(1.f, 0.f, 0.f, 0.f,
		0.f, coshf(d), 0.f, sinhf(d),
		0.f, 0.f, 1.f, 0.f,
		0.f, -sinhf(d), 0.f, coshf(d));
}

Matrix HyperbolicRotationYZ(float d)
{
	return Matrix();
}

Matrix HyperbolicRotationXZ(float d)
{
	return Matrix();
}

Matrix HyperbolicRotationXY(float d)
{
	return Matrix();
}
