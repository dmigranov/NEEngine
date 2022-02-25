#include "SelectionSystem.h"

#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"
#include "SphericalRenderingComponent.h"
#include "InputComponent.h"
#include "SphericalEffect.h"
#include "Game.h"
#include "Scene.h"
#include "Entity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


SelectionSystem::SelectionSystem(InputComponent* pInputComponent, double initialObjectRadius) : m_game(Game::GetInstance())
{
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<SphericalRenderingComponent>();

	m_pInputComponent = pInputComponent;
	m_initialObjectRadius = initialObjectRadius;
	m_pCameraTransform = m_game.GetScene()->GetCamera()->GetComponent<SphericalTransformComponent>();
	m_pCameraComponent = m_game.GetScene()->GetCamera()->GetComponent<SphericalCameraComponent>();
}

void SelectionSystem::Execute(double deltaTime)
{
	auto ms = m_pInputComponent->GetMouseState();

	double radius = SphericalEffect::GetRadius();
	auto cameraPos = m_pCameraTransform->GetSphericalPosition();

	auto w_sphere = radius - 2 * radius * pow(sin(m_initialObjectRadius / radius / 2), 2);
	auto r_sphere = sqrt(radius * radius - w_sphere * w_sphere);

	float minDist = 100000.;
	int minIndex = -1;

	const auto& view = m_pCameraTransform->GetView();
	const Matrix& proj = m_pCameraComponent->GetProj();

	int width, height;
	m_game.GetWindowSize(width, height);

	for (auto pEntity : m_entities)
	{
		//todo
		//добавить в doppler component bool - выбран не выбран?
		//а хотя это и так есть! 
		//и доп. массив с булями не нужен!
	}
}
