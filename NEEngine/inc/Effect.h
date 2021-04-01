#pragma once
#include <string>

class Entity;

// Effect AKA Material. Abstraction for shaders, contains all the buffers and textures.
// Each entity has an effect?
// Or should each mesh have an effect?
// Any way, effects depend on stuff like transforms...
class Effect
{
public:
	//Effect - €вл€етс€ частью Mesh?
	//TODO: Effect - интерфейс/абстрактный класс !!!
	//мы можем от него наследоватьс€, там мы создаЄм буферы и настраиваем их на каждом кадре
	//у каждого наследника - свои констукторы и сеттеры (напр, туман)

	//эффект сам заполн€ет в том числе и матрицу проекции и вида (читает ее откуда-то или в качестве аргумента приходит )
	
	//todo: Input assembly - тоже эффект: в эффекте определена нужна€ стуктура ,
	//и Mesh создаетс€ именно с такой <Struct>
	//Input assembly соответсвует

	Effect();
	virtual ~Effect();
	virtual bool Initialize() = 0;

	virtual bool SetMaterial(const Entity* pEntity) = 0;

	virtual bool Deinitialize() = 0;

	bool IsInited();

protected: 
	bool m_isInited = false;
	std::string magic;



	/*
	enum ConstantBuffer
	{
		CB_Application, //The application level constant buffer stores variables that rarely change. 
		CB_Frame,       //The frame level constant buffer stores variables that change each frame. An example of a frame level shader variable would be the cameraТs view matrix which changes whenever the camera moves
		CB_Object,      //The object
		level constant buffer stores variables that are different for every object being rendered. An example of an object level shader variable is the objectТs world matrix.
		NumConstantBuffers
	};

	//three constant buffers: buffers are used to store shader variables that remain constant during current draw call. An example of a constant shader variable is the cameraТs projection matrix. Since the projection matrix will be the same for every vertex of the object, this variable does not need to be passed to the shader using vertex data.
	ID3D11Buffer* g_d3dVSConstantBuffers[NumConstantBuffers];
	*/



};

