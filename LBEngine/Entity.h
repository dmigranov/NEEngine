#pragma once
#include <list>
#include <string>

class Component;
class Mesh;

/**
* @brief Basic class for all entities (objects) in the scene.
*/
class Entity
{
public:
	Entity(const char* name = nullptr);
	~Entity();

	void Initialize();

	void AddComponent(Component* pComponent);


	void Update();
private:

	/**
	* @brief Contains shaders and texture.
	*/
	Mesh* m_pMesh;
	std::list<Component*> m_components;
	bool m_isActive;
	std::string m_name;
};

