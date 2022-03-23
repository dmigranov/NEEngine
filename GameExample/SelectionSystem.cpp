#include "main.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


SelectionSystem::SelectionSystem(InputComponent* pInputComponent, FriedmannTimer * timer, double initialObjectRadius) : m_game(Game::GetInstance())
{
	
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<SphericalRenderingComponent>();
	SubscribeToComponentType<DopplerComponent>();

	
	m_pInputComponent = pInputComponent;
	m_initialObjectRadius = initialObjectRadius;
	m_pCameraTransform = m_game.GetScene()->GetCamera()->GetComponent<SphericalTransformComponent>();
	m_pCameraComponent = m_game.GetScene()->GetCamera()->GetComponent<SphericalCameraComponent>();
	m_pTimer = timer;
}

void SelectionSystem::Execute(double deltaTime)
{
	auto ms = m_pInputComponent->GetMouseState();

	double radius = SphericalEffect::GetRadius();
	auto cameraPos = m_pCameraTransform->GetSphericalPosition();

	auto w_sphere = radius - 2 * radius * pow(sin(m_initialObjectRadius / radius / 2), 2);
	auto r_sphere = sqrt(radius * radius - w_sphere * w_sphere);

	m_minDistance = 1000000.;
	m_pSelectedEntity = nullptr;
	m_selectedIndex = -1;

	const auto& view = m_pCameraTransform->GetView();
	const Matrix& proj = m_pCameraComponent->GetProj();

	int width, height;
	m_game.GetWindowSize(width, height);
	auto mu = m_pTimer->GetMu();

	//for (auto pEntity : m_entities)
	for (int i = 0; i < m_entities.size(); i++)
	{
		//todo
		//добавить в doppler component bool - выбран не выбран?
		//а хотя это и так есть! 
		//и доп. массив с булями не нужен!
		Entity* pEntity = m_entities[i];

		auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
		auto pRendering = pEntity->GetComponent<SphericalRenderingComponent>();
		auto visibility = pRendering->GetSphericalVisibility();
		if (visibility == SphericalVisibility::VISIBLE_NONE || !pEntity->IsVisible())
			continue;

		const auto& world = pTransform->GetWorld();

		double mouseX = (double)ms.x / width * 2. - 1.;
		double mouseY = -((double)ms.y / height * 2. - 1);

		double t = RayTraceSphereMouse(mouseX, mouseY, pTransform, view, proj, r_sphere, w_sphere);
		if (t < 0)
			continue;

		if (t > 1 && visibility == SphericalVisibility::VISIBLE_FRONT) //back copies aren't visible, so we just continue
			continue;

		if (t < m_minDistance) {
			m_minDistance = t;
			m_pSelectedEntity = pEntity;
			m_selectedIndex = i;
		}
	}
	
}

Entity* SelectionSystem::GetSelectedEntity()
{
	return m_pSelectedEntity;
}

int SelectionSystem::GetSelectedIndex()
{
	return m_selectedIndex;
}

std::vector<Entity*> SelectionSystem::GetEntities()
{
	return m_entities;
}
