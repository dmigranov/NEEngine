#pragma once
#include <list>
#include <string>

class Component;
class TransformComponent;
class Mesh;

/**
* @brief Basic class for all entities (objects) in the scene.
*/

//todo: Camera должна наследоваться от Entity
class Entity
{
public:
	Entity(const char* name = nullptr);
	~Entity();

	void Initialize();

	void AddComponent(Component* pComponent);

	void Update();
private:
	TransformComponent* m_pTransform;
	//EffectComponent* m_pEffect; //todo
	Mesh* m_pMesh; //todo: превратить в компонент?

	std::list<Component*> m_components;
	bool m_isActive;
	std::string m_name;
};

