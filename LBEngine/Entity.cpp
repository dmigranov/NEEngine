#include "pch.h"
#include "Entity.h"

#include "Component.h"


Entity::Entity(const char* name) : 
	m_isActive(false)
{
	m_name = (NULL == name) ? "Object" : name;
}

Entity::~Entity()
{
	
	for(auto pComponent : m_components)
	{
		if (pComponent != nullptr)
			delete pComponent;
	}
	m_components.clear();

	/*if (NULL != m_pEffect)
	{
		m_pEffect->Deinit();
		delete m_pEffect;
		m_pEffect = NULL;
	}*/

	if (NULL != m_pMesh)
	{
		//todo
		/*m_pMesh->Deinit();
		delete m_pMesh;
		m_pMesh = NULL;*/
	}

	/*if (NULL != m_pTransform)
	{
		delete m_pTransform;
		m_pTransform = NULL;
	}*/
}

void Entity::AddComponent(Component* pComponent)
{
	m_components.push_back(pComponent);
	pComponent->Initialize(this);
}

void Entity::Update()
{
	for (auto pComponent : m_components)
	{
		if (pComponent != nullptr) pComponent->Update();

	}
}
