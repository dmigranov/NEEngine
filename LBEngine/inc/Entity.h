#pragma once
#include <list>
#include <string>
#include <map>
#include <typeindex>

class Component;
class TransformComponent;
class RenderComponent;
class Mesh;
enum class ComponentType;

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

	void AddComponent(const ComponentType type, Component* pComponent);
	void SetMesh(Mesh * pMesh);
	Component* GetComponent(ComponentType type);

private:

	//TransformComponent* m_pTransform;
	//EffectComponent* m_pEffect; //todo
	Mesh* m_pMesh = nullptr;

	std::map<ComponentType, Component*> m_components;	
	bool m_isActive;
	std::string m_name;


};



