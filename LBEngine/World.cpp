#include "pch.h"
#include "World.h"

#include "Entity.h"
#include "Camera.h"


World::World() : m_pCamera(nullptr)
{}

World::~World()
{
	//удаление объектов...
}

void World::AddEntity(Entity* pEntity)
{
	if (pEntity == nullptr)
	{
		return;
	}

	//pEntity->Initialize();
	m_entities.push_back(pEntity);
	//ObjectStorage::Push(pObject);
}

void World::SetCamera(Camera* pCamera)
{
	if (pCamera != nullptr)
	{
		m_pCamera = pCamera;
	}
}

Camera* World::GetCamera()
{
	return m_pCamera;
}

void World::Update()
{
	//m_pCamera->GetObjectPtr()->Update();

	//std::list<const Object *>::iterator iter;
	//for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	for (auto pEntity : m_entities)
	{
		if (pEntity != nullptr)
		{
			pEntity->Update();
		}
	}
}

void World::Render()
{
	/*
	//TODO
	if (NULL == m_pCamera)
	{
		return;
	}

	m_pCamera->Render();*/
}
