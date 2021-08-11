#include "pch.h"
#include "HyperbolicMath.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

DirectX::SimpleMath::Matrix HyperbolicRotationYZ(double d)
{
	return Matrix(1.f, 0.f, 0.f, 0.f,
		0.f, cosf(d), -sinf(d), 0.f,
		0.f, sinf(d), cosf(d), 0.f,
		0.f, 0.f, 0.f, 1.f);
}

DirectX::SimpleMath::Matrix HyperbolicRotationXZ(double d)
{
	return Matrix(cosf(d), 0.f, -sinf(d), 0.f,
		0.f, 1.f, 0.f, 0.f,
		sinf(d), 0.f, cosf(d), 0.f,
		0.f, 0.f, 0.f, 1.f);
}

DirectX::SimpleMath::Matrix HyperbolicRotationXY(double d)
{
	return Matrix(cosf(d), -sinf(d), 0.f, 0.f,
		sinf(d), cosf(d), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
