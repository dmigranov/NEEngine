#pragma once
#include <string>

class Entity;

//todo: ƒќЅј¬»“№ RENDER MAP дл€ эффективного рендеринга 
//и рендерить в соответсиви€ми с очередью

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

	virtual void UpdatePerObject(const Entity* pEntity) = 0;

	virtual void Deinitialize() = 0;

	bool IsInited();

protected: 
	bool m_isInited = false;
	std::string magic;



};

