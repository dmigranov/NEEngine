#include "pch.h"
#include "Scene.h"

#include "Entity.h"
#include "System.h"

#include "TransformComponent.h"
#include "CameraComponent.h"

#include "Game.h"
#include "Sound.h"


Scene::Scene() : m_pCamera(nullptr), m_game(Game::GetInstance())
{
}

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

void Scene::SetCamera(Entity* pCamera, CameraComponent* pCameraComponent)
{
	if (pCamera != nullptr)
	{
		pCamera->AddComponent<CameraComponent>(pCameraComponent);
		m_pCamera = pCamera;
		UpdateProjMatrix();
	}
}

Entity* Scene::GetCamera()
{
	return m_pCamera;
}

/*			//Оставить для евклидова случая (обычный, евклидов, движок): там все единообразно...
DirectX::SimpleMath::Matrix Scene::GetProj()
{
	return m_proj;
}

DirectX::SimpleMath::Matrix Scene::GetView()
{
	return m_pCamera->GetTransform()->GetView();
}
*/

void Scene::SetCameraOutputSize(double width, double height)
{
	m_width = width;
	m_height = height;
	if(m_pCamera != nullptr)
	{
		UpdateProjMatrix();
	}

	//todo: передать? или наоборот из камеры получить!
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

double Scene::GetWidth()
{
	return m_width;
}

double Scene::GetHeight()
{
	return m_height;
}

void Scene::AddAndPlayLoopedSound(Sound* sound)
{
	sound->Play(true);
	m_loopingSounds.push_back(sound);
}

void Scene::UpdateProjMatrix()
{
	auto cc = m_pCamera->GetComponent<CameraComponent>();
	cc->SetOutputSize(m_width, m_height);

	//auto proj = cc->GetProj();
	//m_proj = proj; //тут что то с типами...
}

void Scene::ResetLoopedSounds() 
{
	for (auto pSound : m_loopingSounds)
	{
		if (pSound != nullptr)
			pSound->Play(true);
	}
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

void Scene::Render(double delta)
{
	m_game.StartDrawing();	
	
	for (auto pSystem : m_drawingSystems)
	{
		if (pSystem != nullptr)
		{
			pSystem->Execute(delta);
		}
	}

	{	
		//(старая система рендеринга отключена)
		//for (auto p_entity : m_entities)
		//	p_entity->Render();
	}

	m_game.FinishDrawing();

}
