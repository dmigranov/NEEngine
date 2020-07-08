#pragma once

class Camera
{
public:
	struct Rect
	{
		Rect(float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f)
			: x(x), y(y), w(w), h(h)
		{ }

		float x, y, w, h;
	};

	Camera();

	void SetPosition(double x, double y, double z);
	void SetPosition(DirectX::SimpleMath::Vector3 v);

	void SetLookAt(DirectX::SimpleMath::Vector3 v);

	virtual void Move(DirectX::SimpleMath::Vector3 v);
	virtual DirectX::SimpleMath::Vector4 GetPosition();

	virtual void ChangePitchYawRoll(double pitch, double yaw, double roll);

	// Установка вертикального угла обзора (в градусах)
	void SetFovY(float fovY);
	// Установка ближней отсекающей плоскости
	void SetNearPlane(float nearPlane);
	// Установка дальней отсекающей плоскости
	void SetFarPlane(float farPlane);

	/**
	* @brief Where on the screen is the camera rendered in normalized (!!!) coordinates
	* http://www.gamedev.net/page/resources/_/technical/game-programming/a-room-with-a-view-r3901.
	*/
	//todo: исправить Rectangle, там long!
	void SetViewport(Rect rect = Rect(0.0f, 0.0f, 1.0f, 1.0f));
	void SetOutputSize(double outputWidth, double outputHeight);


	virtual const DirectX::XMMATRIX& GetView();
	virtual const DirectX::XMMATRIX& GetProj();
	virtual const DirectX::XMMATRIX& GetCameraTransform();


protected:

	void RecalculateMatrixProj();

	DirectX::SimpleMath::Vector3 m_position;
	double m_pitch;
	double m_yaw;
	double m_roll;


	DirectX::SimpleMath::Vector3 m_lookAt;

	// Background color
	float m_r, m_g, m_b;

	// Render texture (if it's NULL then render to the screen, otherwise - to m_pRenderTexture)
	//const RenderTexture* m_pRenderTexture;

	// Вертикальный угол обзора в градусах
	float m_fovY;
	float m_nearPlane;
	float m_farPlane;

	DirectX::XMMATRIX m_proj;
	DirectX::XMMATRIX m_view;

	bool m_viewDirty;

	Rect m_viewport;

	double m_outputWidth, m_outputHeight;
};

