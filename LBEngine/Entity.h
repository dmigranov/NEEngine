#pragma once
#include <list>

class Component;

/**
* @brief Basic class for all entities (objects) in the scene.
*/
class Entity
{
public:
	Entity(const char* name = nullptr);

private:
	std::list<Component*> m_components;
};

