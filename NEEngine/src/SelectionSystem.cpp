#include "SelectionSystem.h"

#include "SphericalTransformComponent.h"
#include "SphericalRenderingComponent.h"
#include "InputComponent.h"
#include "SphericalEffect.h"
#include "Game.h"
#include "Scene.h"
#include "Entity.h"

using namespace DirectX;

SelectionSystem::SelectionSystem(InputComponent* pInputComponent, double initialObjectRadius) : m_game(Game::GetInstance())
{
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<SphericalRenderingComponent>();

	m_pInputComponent = pInputComponent;
	m_initialObjectRadius = initialObjectRadius;
	m_pCameraTransform = m_game.GetScene()->GetCamera()->GetComponent<SphericalTransformComponent>();
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
	const Matrix& proj = cameraComponent->GetProj();

	int width, height;
	game.GetWindowSize(width, height);
}
