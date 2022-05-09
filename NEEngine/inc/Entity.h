#pragma once
#include <list>
#include <string>
#include <map>
#include <typeindex>
#include <boost/dynamic_bitset.hpp>

#include "ComponentTypeManager.h"
#include "Component.h"


class Game;
class TransformComponent;
class MeshComponent;

/**
* @brief Basic class for all entities (objects) in the scene.
*/

class Entity
{
public:
	Entity(bool isVisible = true, const char* name = nullptr);
	~Entity();

	void Initialize();

	//void SetMesh(MeshComponent* pMesh);
	//void SetTransform(TransformComponent* pTransform);
	//TransformComponent* const GetTransform();

	void Render();

	void SetVisible(bool isVisible);
	bool IsVisible() const;

	std::string GetName() const;

	//void AddComponent(const ComponentType type, Component* pComponent);	//old
	
	//было Component*, сделал T*
	template<typename T> void AddComponent(T* pComponent)		//new 
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
	template<typename T> T* GetComponent() const	//new; const - can't modify the object it's invoked on
	{
		auto index = Game::GetInstance().GetComponentTypeManager()->template GetComponentTypeIndex<T>(); //if such a type isn't registered, will return default value - 0
		return static_cast<T*>(m_components[index]); //if doesn't exist, than zero (considering that not out of bounds)
	}

	const boost::dynamic_bitset<>& GetComponentsMask();

private:

	//EffectComponent* m_pEffect; //todo
	MeshComponent* m_pMesh = nullptr;
	TransformComponent* m_pTransform = nullptr;
	//std::map<ComponentType, Component*> m_components;	
	std::vector<Component*> m_components;

	bool m_isActive;

	bool m_isVisible;

	std::string m_name;

	//std::bitset<COMPONENT_TYPE_COUNT> m_componentsMask;

	boost::dynamic_bitset<> m_componentsMask;
};

