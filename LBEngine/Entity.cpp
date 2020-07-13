#include "pch.h"
#include "Entity.h"

#include "ComponentType.h"
#include "Component.h"
#include "TransformComponent.h"
#include "inc\Entity.h"

Entity::Entity(const char* name) : 
	m_isActive(false)
{
	m_name = (nullptr == name) ? "Object" : name;

	//m_pTransform = new TransformComponent();
	//AddComponent(m_pTransform);

	m_pMesh = nullptr;
}

Entity::~Entity()
{
	for(auto pair : m_components)
	{
		if (pair.second != nullptr)
			delete pair.second;
	}
	m_components.clear();

	/*if (nullptr != m_pEffect)
	{
		m_pEffect->Deinit();
		delete m_pEffect;
		m_pEffect = NULL;
	}*/

	if (nullptr != m_pMesh)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}

	/*if (NULL != m_pTransform)
	{
		delete m_pTransform;
		m_pTransform = NULL;
	}*/
}

void Entity::Initialize()
{
	//todo
	/*if (m_pMesh != nullptr)
	{
		m_pMesh->Init();
	}

	if ( m_pEffect != nullptr)
	{
		m_pMaterial->Init();
	}*/
}

void Entity::AddComponent(const ComponentType type, Component* pComponent)
{
	m_components.insert(std::pair<ComponentType, Component*>(type, pComponent));
	pComponent->Initialize(this);
}

void Entity::SetMesh(Mesh* pMesh)
{
	m_pMesh = pMesh;
}

Component* Entity::GetComponent(ComponentType type)
{
	return m_components[type];
}
