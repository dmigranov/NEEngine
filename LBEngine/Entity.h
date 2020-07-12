#pragma once
#include <list>

class Component;
class Mesh;

/**
* @brief Basic class for all entities (objects) in the scene.
*/
class Entity
{
public:
	Entity(const char* name = nullptr);
	void AddComponent(Component* pComponent);
private:

	/**
	* @brief Contains shaders and texture.
	*/
	Mesh* mesh;
	std::list<Component*> m_components;
	bool m_isActive;
	std::string m_name;
};

