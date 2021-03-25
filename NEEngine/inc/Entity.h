#pragma once
#include <list>
#include <string>
#include <map>
#include <typeindex>
#include <boost/dynamic_bitset.hpp>

#include "VertexTexMeshComponent.h"
#include "ComponentTypeManager.h"

class Component;
class TransformComponent;
class RenderComponent;
class Game;


/**
* @brief Basic class for all entities (objects) in the scene.
*/

class Entity
{
public:
	Entity(const char* name = nullptr);
	~Entity();

	void Initialize();

	void SetMesh(VertexTexMeshComponent * pMesh);
	void SetTransform(TransformComponent* pTransform);
	TransformComponent* const GetTransform();

	void Render();

	//void AddComponent(const ComponentType type, Component* pComponent);	//old
	template<typename T> void AddComponent(Component* pComponent)		//new
	{
		auto manager = Game::GetInstance().GetComponentTypeManager();
		auto componentIndex = manager->template GetComponentTypeIndex<T>();
		m_components[componentIndex] = pComponent;
		pComponent->Initialize(this);

		boost::dynamic_bitset<> add(manager->GetComponentTypesCount());
		add[componentIndex] = 1;
		m_componentsMask |= add;
	}

	//Component* GetComponent(ComponentType type);	//old
	template<typename T> T* GetComponent()			//new
	{
		return static_cast<T*>(m_components[Game::GetInstance().GetComponentTypeManager()->template GetComponentTypeIndex<T>()]);
	}

	const boost::dynamic_bitset<>& GetComponentsMask();

private:

	//EffectComponent* m_pEffect; //todo
	VertexTexMeshComponent* m_pMesh = nullptr;
	TransformComponent* m_pTransform = nullptr;
	//std::map<ComponentType, Component*> m_components;	
	std::vector<Component*> m_components;

	bool m_isActive;
	std::string m_name;

	//std::bitset<COMPONENT_TYPE_COUNT> m_componentsMask;

	boost::dynamic_bitset<> m_componentsMask;
};

