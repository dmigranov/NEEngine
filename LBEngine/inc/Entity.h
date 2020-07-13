#pragma once
#include <list>
#include <string>
#include <map>
#include <typeindex>

#include "MeshComponent.h"

class Component;
class TransformComponent;
class RenderComponent;
enum class ComponentType;

/**
* @brief Basic class for all entities (objects) in the scene.
*/

//todo: Camera должна наследоваться от Entity
class Entity
{
public:
	struct VertexPosTex
	{
		DirectX::XMFLOAT4 Position;  //координаты точки в четырехмерном пространстве
		DirectX::XMFLOAT4 Color;
		DirectX::XMFLOAT2 TexCoord;
	};


	Entity(const char* name = nullptr);
	~Entity();

	void Initialize();

	void AddComponent(const ComponentType type, Component* pComponent);
	void SetMesh(MeshComponent<VertexPosTex> * pMesh);
	void SetTransform(TransformComponent* pTransform);

	void Render();

	Component* GetComponent(ComponentType type);

private:

	//EffectComponent* m_pEffect; //todo
	MeshComponent<VertexPosTex>* m_pMesh = nullptr;
	TransformComponent* m_pTransform = nullptr;
	std::map<ComponentType, Component*> m_components;	
	bool m_isActive;
	std::string m_name;


};



