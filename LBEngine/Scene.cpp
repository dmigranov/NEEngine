#include "pch.h"
#include "Scene.h"

#include "Entity.h"
#include "System.h"
#include "Camera.h"


Scene::Scene() : m_pCamera(nullptr)
{}

Scene::~Scene()
{
	//удаление объектов...
}

void Scene::AddEntity(Entity* pEntity)
{
	if (pEntity == nullptr)
	{
		return;
	}

	//pEntity->Initialize();
	m_entities.push_back(pEntity);
	//ObjectStorage::Push(pObject);
}

void Scene::SetCamera(Camera* pCamera)
{
	if (pCamera != nullptr)
	{
		m_pCamera = pCamera;
	}
}

Camera* Scene::GetCamera()
{
	return m_pCamera;
}

void Scene::Update()
{
	//m_pCamera->GetObjectPtr()->Update();

	//std::list<const Object *>::iterator iter;
	//for (iter = m_objects.begin(); iter != m_objects.end(); iter++)
	for (auto pSystem : m_systems)
	{
		if (pSystem != nullptr)
		{
			pSystem->Update();
		}
	}
}

void Scene::Render()
{
	/*
	//TODO
	if (NULL == m_pCamera)
	{
		return;
	}

	m_pCamera->Render();*/
}
