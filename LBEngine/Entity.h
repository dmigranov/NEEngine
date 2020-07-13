#pragma once
#include <list>
#include <string>

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

	void AddComponent(Component* pComponent);
private:
	template <class T, class F> bool isFTypeT(F* f) { return false; }
	template <class T, class F> bool isFTypeT(T* f) { return true; }


	//TransformComponent* m_pTransform;
	//EffectComponent* m_pEffect; //todo
	Mesh* m_pMesh;

	std::list<Component*> m_components;
	bool m_isActive;
	std::string m_name;

public:
	template <class T> T* GetComponent();

};

template<class T>
inline T* Entity::GetComponent()
{
	for (Component* pComponent : m_components)
	{
		if (isFTypeT<Component, T>(pComponent))
			return (T*)pComponent;
	}
	return nullptr;
}


