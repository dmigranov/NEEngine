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

	while (!m_nonDrawingSystems.empty())
	{
		delete m_nonDrawingSystems.front();
		m_nonDrawingSystems.erase(m_nonDrawingSystems.begin());
	}

	while (!m_drawingSystems.empty())
	{
		delete m_drawingSystems.front();
		m_drawingSystems.erase(m_drawingSystems.begin());
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

void Scene::AddSystem(System* pSystem)
{
	if (pSystem == nullptr)
	{
		return;
	}
	if(pSystem->m_isDrawing)
		m_drawingSystems.push_back(pSystem);
	else
		m_nonDrawingSystems.push_back(pSystem);
}

void Scene::SetCamera(Entity* pCamera)
{
	//todo: сделать всякие проверки на то, есть ли компонент...

	if (pCamera != nullptr)
	{
		m_pCamera = pCamera;
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
		for (auto pSystem : m_nonDrawingSystems)
		{
			if ((pSystem->GetComponentsMask() & pEntity->GetComponentsMask()) == pSystem->GetComponentsMask())
				pSystem->AddEntity(pEntity);
		}
		for (auto pSystem : m_drawingSystems)
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

void Scene::Update(double delta)
{
	for (auto pSystem : m_nonDrawingSystems)
	{
		if (pSystem != nullptr)
		{
			pSystem->Execute(delta);
		}
	}
}

void Scene::Render()
{
	m_game.StartDrawing();

	const auto view = m_pCamera->GetTransform()->GetView();
	
	
	m_game.g_d3dDeviceContext->UpdateSubresource(m_game.g_d3dVSConstantBuffers[m_game.CB_Frame], 0, nullptr, &view, 0, 0);

	for (auto pSystem : m_drawingSystems)
	{
		if (pSystem != nullptr)
		{
			pSystem->Execute(0);
		}
	}

	{	//todo: старая система рендера, переделать
		for (auto p_entity : m_entities)
			p_entity->Render();
	}

	m_game.FinishDrawing();

}
