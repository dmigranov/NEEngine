#include "pch.h"
#include "SphericalMath.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

//z0 - radians
//gives 90 degree FOV
Matrix BananaProjectionMatrix(double z0)
{
	return Matrix(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 0.5f, 1.f,
		0.f, 0.f, -z0/2.f, 0);
}

Matrix BananaProjectionMatrix(double fovY, double aspect, double z0)
{
	float height = 1.f / tanf(fovY/2);
	float width = height / aspect;
	return Matrix(width, 0.f, 0.f, 0.f,
		0.f, height, 0.f, 0.f,
		0.f, 0.f, 0.5f, 1.f,
		0.f, 0.f, -z0 / 2.f, 0);
}

Matrix BananaProjectionMatrixFrontHalf(double z0)
{
	return Matrix(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 0.25f, 1.f,
		0.f, 0.f, -z0 / 4.f, 0);
}

Matrix BananaProjectionMatrixFrontHalf(double fovY, double aspect, double z0)
{
	float height = 1.f / tanf(fovY / 2);
	float width = height / aspect;
	return Matrix(width, 0.f, 0.f, 0.f,
		0.f, height, 0.f, 0.f,
		0.f, 0.f, 0.25f, 1.f,
		0.f, 0.f, -z0 / 4.f, 0);
}

Matrix BananaProjectionMatrixBackHalf(double z0)
{
	return Matrix(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 0.75f, 1.f,
		0.f, 0.f, -z0 / 4.f, 0);
}

Matrix BananaProjectionMatrixBackHalf(double fovY, double aspect, double z0)
{
	float height = 1.f / tanf(fovY / 2);
	float width = height / aspect;
	return Matrix(width, 0.f, 0.f, 0.f,
		0.f, height, 0.f, 0.f,
		0.f, 0.f, 0.75f, 1.f,
		0.f, 0.f, -z0 / 4.f, 0);
}

//rotation around plane XY which stays invariant
Matrix SphericalRotationZW(float d)
{
	return Matrix(	1.f, 0.f, 0.f, 0.f,
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, cosf(d), -sinf(d),
					0.f, 0.f, sinf(d), cosf(d));
}		

Matrix SphericalRotationXW(float d)
{
	return Matrix(	cosf(d), 0.f, 0.f, -sinf(d),
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					sinf(d), 0.f, 0.f, cosf(d));
}

Matrix SphericalRotationYW(float d)
{
	return Matrix(	1.f, 0.f, 0.f, 0.f,
					0.f, cosf(d), 0.f, -sinf(d),
					0.f, 0.f, 1.f, 0.f,
					0.f, sinf(d), 0.f, cosf(d));
}

Matrix SphericalRotationYZ(float d)
{
	return Matrix(	1.f, 0.f, 0.f, 0.f,
					0.f, cosf(d), -sinf(d), 0.f,
					0.f, sinf(d), cosf(d), 0.f,
					0.f, 0.f, 0.f, 1.f);
}

Matrix SphericalRotationXZ(float d)
{
	return Matrix(	cosf(d), 0.f, -sinf(d), 0.f,
					0.f, 1.f, 0.f, 0.f,
					sinf(d), 0.f, cosf(d), 0.f,
					0.f, 0.f, 0.f, 1.f);
}

Matrix SphericalRotationXY(float d)
{
	return Matrix(	cosf(d), -sinf(d), 0.f, 0.f,
					sinf(d), cosf(d), 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f);
}

float SphericalDistance(DirectX::SimpleMath::Vector4 vec1, DirectX::SimpleMath::Vector4 vec2, double radius)
{

	float chordLength = Vector4::Distance(vec1, vec2); // chord length
	return 2 * radius * asin(chordLength / (2. * radius)); // angle is 2arcsin(L/2R), length of arc equals angle * R
}
