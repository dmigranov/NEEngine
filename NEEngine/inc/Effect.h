#pragma once
#include <string>

// Effect AKA Material. Abstraction for shaders, contains all the buffers and textures.
class Effect
{
public:
	//Effect - является частью Mesh?
	//TODO: Effect - интерфейс/абстрактный класс !!!
	//мы можем от него наследоваться, там мы создаём буферы и настраиваем их на каждом кадре
	//у каждого наследника - свои констукторы и сеттеры (напр, туман)

	Effect();
	virtual ~Effect();
	void Initialize();
	void Deinitialize();
	void Update();
private:
	std::string		m_vsFileName;
	std::string		m_psFileName;

};

