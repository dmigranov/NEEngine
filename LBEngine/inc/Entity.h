#pragma once
#include <list>
#include <string>
#include <map>
#include <typeindex>
#include <bitset>

#include "MeshComponent.h"
#include "ComponentType.h"

class Component;
class TransformComponent;
class RenderComponent;
/**
* @brief Basic class for all entities (objects) in the scene.
*/

class Entity
{
public:
	Entity(const char* name = nullptr);
	~Entity();

	void Initialize();

	void AddComponent(const ComponentType type, Component* pComponent);
	void SetMesh(MeshComponent * pMesh);
	void SetTransform(TransformComponent* pTransform);
	TransformComponent* const GetTransform();

	void Render();

	Component* GetComponent(ComponentType type);
	const std::bitset<COMPONENT_TYPE_COUNT>& GetComponentsMask();
private:

	//EffectComponent* m_pEffect; //todo
	MeshComponent* m_pMesh = nullptr;
	TransformComponent* m_pTransform = nullptr;
	std::map<ComponentType, Component*> m_components;	
	bool m_isActive;
	std::string m_name;

	std::bitset<COMPONENT_TYPE_COUNT> m_componentsMask;
};



