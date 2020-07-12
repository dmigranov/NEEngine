#include "pch.h"
#include "Entity.h"

Entity::Entity(const char* name) : 
	m_isActive(false)
{
	m_name = (NULL == name) ? "Object" : name;
}

void Entity::AddComponent(Component* pComponent)
{
	m_components.push_back(pComponent);
	//pComponent->Initialize(this);
}
