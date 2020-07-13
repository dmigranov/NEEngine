#pragma once
#include <list>
#include <string>
#include <map>
#include <typeindex>

class Component;
class TransformComponent;
class RenderComponent;
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

	void AddComponent(ComponentType type, Component* pComponent);
private:

	//TransformComponent* m_pTransform;
	//EffectComponent* m_pEffect; //todo
	Mesh* m_pMesh;

	std::map<ComponentType, Component*> m_components;	
	bool m_isActive;
	std::string m_name;

public:
	template <class T> T* GetComponent();

};

template<class T>
inline T* Entity::GetComponent()
{

	return nullptr;
}


