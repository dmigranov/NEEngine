#include "pch.h"
#include "HyperbolicMath.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;


DirectX::SimpleMath::Matrix HyperbolicTranslationZW(float d)
{
	return Matrix(	1.f, 0.f, 0.f, 0.f,
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, coshf(d), sinhf(d),
					0.f, 0.f, sinhf(d), coshf(d));
}

DirectX::SimpleMath::Matrix HyperbolicTranslationXW(float d)
{
	return Matrix(	coshf(d), 0.f, 0.f, sinhf(d),
					0.f, 1.f, 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					sinhf(d), 0.f, 0.f, coshf(d));
}

DirectX::SimpleMath::Matrix HyperbolicTranslationYW(float d)
{
	return Matrix(	1.f, 0.f, 0.f, 0.f,
					0.f, coshf(d), 0.f, sinhf(d),
					0.f, 0.f, 1.f, 0.f,
					0.f, sinhf(d), 0.f, coshf(d));
}


DirectX::SimpleMath::Matrix HyperbolicRotationYZ(float d)
{
	return Matrix(	1.f, 0.f, 0.f, 0.f,
					0.f, cosf(d), -sinf(d), 0.f,
					0.f, sinf(d), cosf(d), 0.f,
					0.f, 0.f, 0.f, 1.f);
}

DirectX::SimpleMath::Matrix HyperbolicRotationXZ(float d)
{
	return Matrix(	cosf(d), 0.f, -sinf(d), 0.f,
					0.f, 1.f, 0.f, 0.f,
					sinf(d), 0.f, cosf(d), 0.f,
					0.f, 0.f, 0.f, 1.f);
}

DirectX::SimpleMath::Matrix HyperbolicRotationXY(float d)
{
	return Matrix(	cosf(d), -sinf(d), 0.f, 0.f,
					sinf(d), cosf(d), 0.f, 0.f,
					0.f, 0.f, 1.f, 0.f,
					0.f, 0.f, 0.f, 1.f);
}
