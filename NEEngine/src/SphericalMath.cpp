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


//xyzw
XMFLOAT3 GetSphericalFromCartesian(float x4, float x3, float x2, float x1)
{
	float x42 = x4 * x4;
	float x22 = x2 * x2;
	float x32 = x3 * x3;

	float a1 = acosf(x1);
	if (x2 == 0 && x3 == 0 && x4 == 0)
		if (x1 > 0)
			return Vector3(a1, 0, 0);
		else
			return Vector3(a1, XM_PI, XM_PI);

	float a2 = acosf(x2 / sqrtf(x22 + x32 + x42));
	if (x3 == 0 && x4 == 0)
		if (x2 > 0)
			return Vector3(a1, a2, 0);
		else
			return Vector3(a1, a2, XM_PI);

	float a3;
	if (x4 >= 0)
		a3 = acosf(x3 / sqrtf(x32 + x42));
	else
		a3 = XM_2PI - acosf(x3 / sqrtf(x32 + x42));

	return XMFLOAT3(a1, a2, a3);
}
