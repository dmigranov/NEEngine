#pragma once
#include <string>

class Entity;

//todo: ДОБАВИТЬ RENDER MAP для эффективного рендеринга 
//и рендерить в соответсивиями с очередью

// Effect AKA Material. Abstraction for shaders, contains all the buffers and textures.
// Each entity has an effect?
// Or should each mesh have an effect?
// Any way, effects depend on stuff like transforms...
class Effect
{
public:
	// Effect - абстрактный класс
	// Мы можем от него наследоваться, 
	// В реализации мы создаём буферы и настраиваем их на каждом кадре
	// У каждого наследника - свои констукторы и сеттеры (напр, туман)
	
	// В эффекте определена нужная стуктура 
	// (todo: можно ли это сделать как-то универсальней? чтобы у абст. класса что-то было, что обязаны определить дети?)
	// И Mesh создается именно с такой <Struct>
	
	Effect();
	virtual ~Effect();
	virtual bool Initialize() = 0;

	virtual void UpdatePerObject(const Entity* pEntity) = 0;
	virtual void UpdatePerScene() = 0;
	virtual void UpdatePerApplication() = 0; //todo: последние два - для оптимизации

	virtual unsigned int GetVertexBufferSize() const = 0;

	virtual void Deinitialize() = 0;

	virtual const std::type_info& GetVertexDataType() = 0;
	virtual std::string GetName();
	bool IsInited();

protected: 
	bool m_isInited = false;
	std::string magic;



};

