#pragma once
#include <string>

// Effect AKA Material. Abstraction for shaders, contains all the buffers and textures.
class Effect
{
public:
	//Effect - €вл€етс€ частью Mesh?
	//TODO: Effect - интерфейс/абстрактный класс !!!
	//мы можем от него наследоватьс€, там мы создаЄм буферы и настраиваем их на каждом кадре
	//у каждого наследника - свои констукторы и сеттеры (напр, туман)

	//эффект сам заполн€ет в том числе и матрицу проекции и вида (читает ее откуда-то или в качестве аргумента приходит )

	Effect();
	virtual ~Effect();
	void Initialize();
	void Deinitialize();
	void Update();
private:
	std::string		m_vsFileName;
	std::string		m_psFileName;

	ID3D11VertexShader* g_d3dVertexShader = nullptr;
	ID3D11PixelShader* g_d3dPixelShader = nullptr;

	/*
	enum ConstantBuffer
	{
		CB_Application, //The application level constant buffer stores variables that rarely change. 
		CB_Frame,       //The frame level constant buffer stores variables that change each frame. An example of a frame level shader variable would be the cameraТs view matrix which changes whenever the camera moves
		CB_Object,      //The object level constant buffer stores variables that are different for every object being rendered. An example of an object level shader variable is the objectТs world matrix.
		NumConstantBuffers
	};

	//three constant buffers: buffers are used to store shader variables that remain constant during current draw call. An example of a constant shader variable is the cameraТs projection matrix. Since the projection matrix will be the same for every vertex of the object, this variable does not need to be passed to the shader using vertex data.
	ID3D11Buffer* g_d3dVSConstantBuffers[NumConstantBuffers];
	*/

	ID3D11Buffer* g_d3dVSConstantBuffer; //тк у каждого объекта свой эффект то только один
	//VS буфер - аналог CB_Object
	ID3D11Buffer* g_d3dPSConstantBuffer;

};

