#include "pch.h"
#include "Entity.h"

#include "Game.h"
#include "ComponentTypeManager.h"
#include "Component.h"
#include "TransformComponent.h"

#include "MeshComponent.h"


Entity::Entity(bool isVisible, const char* name) :
	m_isActive(false), m_componentsMask(Game::GetInstance().GetComponentTypeManager()->GetComponentTypesCount()),
	m_components(Game::GetInstance().GetComponentTypeManager()->GetComponentTypesCount()),
	m_isVisible(isVisible)
{
	m_name = (nullptr == name) ? "Object" : name;
	//m_pTransform = new TransformComponent();
	//AddComponent(m_pTransform);

	m_pMesh = nullptr;
}

Entity::~Entity()
{


	//mesh, transform и другие энтити удялялись при удалении всех энтити.
	//но правильно ли удалять компоненты тут, в энтити?
	//ведь компоненты могут быть общими
	//todo: smart ptr?

	m_components.clear();

}

void Entity::Initialize()
{

}

/*void Entity::AddComponent(const ComponentType type, Component* pComponent)
{
	m_components.insert(std::pair<ComponentType, Component*>(type, pComponent));
	pComponent->Initialize(this);

	//boost::dynamic_bitset<> add = (size_t)1 << (size_t)type;	//todo
	boost::dynamic_bitset<> add(Game::GetInstance().GetComponentTypeManager()->GetComponentTypesCount());

	m_componentsMask |= add;
}*/

/*
void Entity::SetMesh(MeshComponent* pMesh)
{
	m_pMesh = pMesh;
	//AddComponent(ComponentType::MeshComponentType, pMesh);
	AddComponent<MeshComponent>(pMesh);
}

void Entity::SetTransform(TransformComponent* pTransform)
{
	m_pTransform = pTransform;
	//AddComponent(ComponentType::TransformComponentType, pTransform);
	AddComponent<TransformComponent>(pTransform);
}

TransformComponent* const Entity::GetTransform()
{
	return m_pTransform;
}
*/

void Entity::Render()
{
	if (m_pMesh == nullptr)
		return;
	//m_pMesh->Render(m_pTransform->GetWorld());
}

void Entity::SetVisible(bool isVisible)
{
	m_isVisible = isVisible;
}

bool Entity::IsVisible() const
{
	return m_isVisible;
}

std::string Entity::GetName() const
{
return m_name;
}



/*Component* Entity::GetComponent(ComponentType type)
{
	//return m_components[type];
	return nullptr;
}*/

const boost::dynamic_bitset<>& Entity::GetComponentsMask()
{
	return m_componentsMask;
}
