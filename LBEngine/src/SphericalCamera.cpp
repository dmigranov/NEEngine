#include "pch.h"
#include "SphericalCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SphericalCamera::SphericalCamera() 
{
	m_view = Matrix::Identity;
}
const XMMATRIX& SphericalCamera::GetView()
{
	if (m_viewDirty)
	{
		//view - это обратная к cameraTransform.
		//чтобы найти камераТрансформ, сначала поворачиваем камеру (слева), потом перемещаем (справа)
		//но (ABC)-1 = C-1 B-1 A-1
		//поэтому при нахождении view вращения камеры СПРАВА
		//А обратная матрица - равна транспонированной!

		//пич йоу:
		//для нахождения камера трансформ сначала pitch, потом yaw. то есть там pitch левее
		//но для view питч будет правее

		//Matrix ROld = SphericalRotationXZ(m_yaw) * SphericalRotationYZ(m_pitch);
		//T = T * R * SphericalRotationZW(m_position.z) * SphericalRotationYW(m_position.y) * SphericalRotationXW(m_position.x) * R.Invert();
		//T = T * SphericalRotationZW(m_position.z) * SphericalRotationYW(m_position.y) * SphericalRotationXW(m_position.x) ;		
		
		Matrix dT = SphericalRotationXW(dV.x) * SphericalRotationYW(dV.y) * SphericalRotationZW(dV.z);
		//Matrix dT = SphericalRotationYW(dV.y) *  SphericalRotationXW(dV.x)  * SphericalRotationZW(dV.z);

		
		//T = T * R * dT * R.Transpose();	//свободное движение с шутерной камерой
		T = T * RYaw * dT * RYaw.Transpose();	//движение в одной плоскости
		
		m_view = T * R ;

		dV = Vector3::Zero;
	}
	return m_view;
}

const XMMATRIX& SphericalCamera::GetAntipodalView()
{
	return -(m_view);
}

const XMMATRIX& SphericalCamera::GetProj()
{
	m_proj = BananaProjectionMatrix(m_nearPlane);

	return m_proj;
}

const XMMATRIX& SphericalCamera::GetFrontProj()
{
	double sw = m_outputWidth;
	double sh = m_outputHeight;

	double vw = m_viewport.w;
	double vh = m_viewport.h;

	float aspect = (float)((sw * vw) / (sh * vh));
	Matrix front = BananaProjectionMatrixFrontHalf(m_fovY, aspect, m_nearPlane);
	return front;
}

const XMMATRIX& SphericalCamera::GetBackProj()
{
	double sw = m_outputWidth;
	double sh = m_outputHeight;

	double vw = m_viewport.w;
	double vh = m_viewport.h;

	float aspect = (float)((sw * vw) / (sh * vh));
	Matrix back = BananaProjectionMatrixBackHalf(m_fovY, aspect, m_nearPlane);
	return back;
}

const XMMATRIX& SphericalCamera::GetEllipticalProj()
{
	double sw = m_outputWidth;
	double sh = m_outputHeight;

	double vw = m_viewport.w;
	double vh = m_viewport.h;

	float aspect = (float)((sw * vw) / (sh * vh));
	Matrix ell = BananaProjectionMatrix(m_fovY, aspect, m_nearPlane);
	return ell;
}

const DirectX::XMMATRIX& SphericalCamera::GetCameraTransform()
{
	return ((Matrix)m_view).Transpose();
}

Vector4 SphericalCamera::GetPosition()
{
	return XMVector4Transform(spherePos, ((Matrix)m_view).Transpose());
}

//v = dx dy dz (градусы)
void SphericalCamera::Move(Vector3 v3)
{
	dV = v3;

	m_viewDirty = true;
}


void SphericalCamera::ChangePitchYawRoll(double deltaPitch, double deltaYaw, double deltaRoll)
{
	Camera::ChangePitchYawRoll(deltaPitch, deltaYaw, deltaRoll);
	pitchDelta = deltaPitch;
	yawDelta = deltaYaw;

	RYaw = SphericalRotationXZ(m_yaw);
	RPitch = SphericalRotationYZ(m_pitch);

	RInv = SphericalRotationYZ(-m_pitch) * SphericalRotationXZ(-m_yaw);
	R = RYaw * RPitch;

	/*auto RQuat = XMQuaternionRotationRollPitchYaw(m_pitch, -m_yaw, m_roll);
	Matrix RQuatM = XMMatrixRotationQuaternion(RQuat);
	R = RQuatM;
	RInv = R.Invert();
	m_viewDirty = true;*/


}


//xyzw
XMFLOAT3 SphericalCamera::GetSphericalFromCartesian(float x4, float x3, float x2, float x1)
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


