#include "pch.h"
#include "Scene.h"

#include "Entity.h"
#include "System.h"
#include "Camera.h"

#include "TransformComponent.h"
#include "CameraComponent.h"
#include "ComponentType.h"

#include "Game.h"


Scene::Scene() : m_pCamera(nullptr), m_game(Game::GetInstance())
{}

Scene::~Scene()
{
	while (!m_entities.empty())
	{
		delete m_entities.front();
		m_entities.erase(m_entities.begin());
	}

	while (!m_systems.empty())
	{
		delete m_systems.front();
		m_systems.erase(m_systems.begin());
	}
	//todo: camera?
}

void Scene::AddEntity(Entity* pEntity)
{
	if (pEntity == nullptr)
	{
		return;
	}
	pEntity->Initialize();
	m_entities.push_back(pEntity);
}

void Scene::AddSystem(System* pSystem)
{
	if (pSystem == nullptr)
	{
		return;
	}
	m_systems.push_back(pSystem);
}

void Scene::SetCamera(Entity* pCamera)
{
	//надо ли добавлять камеру в ентити?
	if (pCamera != nullptr)
	{
		m_pCamera = pCamera;
		m_pCamera->AddComponent(ComponentType::CameraComponentType, new CameraComponent());
		UpdateProjMatrix();
	}
}

Entity* Scene::GetCamera()
{
	return m_pCamera;
}

void Scene::SetCameraOutputSize(double width, double height)
{
	m_width = width;
	m_height = height;
	if(m_pCamera != nullptr)
	{
		UpdateProjMatrix();
	}
}

void Scene::SynchronizeSystemsWithEntities()
{
	for (auto pEntity : m_entities)
	{
		for (auto pSystem : m_systems)
		{
			if ((pSystem->GetComponentsMask() & pEntity->GetComponentsMask()) == pSystem->GetComponentsMask())
				pSystem->AddEntity(pEntity);
		}
	}
}

void Scene::UpdateProjMatrix()
{
	//todo: оптимизировать: сохранить в поле?

	auto cc = (CameraComponent*)(m_pCamera->GetComponent(ComponentType::CameraComponentType));
	cc->SetOutputSize(m_width, m_height);

	auto proj = cc->GetProj();

	m_game.g_d3dDeviceContext->UpdateSubresource(m_game.g_d3dVSConstantBuffers[m_game.CB_Application], 0, nullptr, &proj, 0, 0);
}

void Scene::Update()
{
	//m_pCamera->GetObjectPtr()->Update();

	for (auto pSystem : m_systems)
	{
		if (pSystem != nullptr)
		{
			pSystem->Execute();
		}
	}
}

void Scene::Render()
{
	const auto view = m_pCamera->GetTransform()->GetView();

	m_game.g_d3dDeviceContext->UpdateSubresource(m_game.g_d3dVSConstantBuffers[m_game.CB_Frame], 0, nullptr, &view, 0, 0);

	for (auto p_entity : m_entities)
		p_entity->Render();
}
