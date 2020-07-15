#include "pch.h"
#include "Scene.h"

#include "Entity.h"
#include "System.h"
#include "Camera.h"

#include "TransformComponent.h"

#include "Game.h"


Scene::Scene() : m_pCamera(nullptr)
{}

Scene::~Scene()
{
	while (!m_entities.empty())
	{
		delete m_entities.front();
		m_entities.erase(m_entities.begin());
	}
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

void Scene::SetCamera(Entity* pCamera)
{
	if (pCamera != nullptr)
	{
		m_pCamera = pCamera;
	}
}

Entity* Scene::GetCamera()
{
	return m_pCamera;
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

	auto& game = Game::GetInstance();

	game.g_d3dDeviceContext->UpdateSubresource(game.g_d3dVSConstantBuffers[game.CB_Frame], 0, nullptr, &view, 0, 0);

	for (auto p_entity : m_entities)
		p_entity->Render();
}
