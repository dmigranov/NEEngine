#include "SelectionSystem.h"

#include "SphericalTransformComponent.h"
#include "SphericalRenderingComponent.h"
#include "InputComponent.h"
#include "SphericalEffect.h"
#include "Game.h"
#include "Scene.h"


SelectionSystem::SelectionSystem(InputComponent* pInputComponent) : m_game(Game::GetInstance())
{
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<SphericalRenderingComponent>();

	m_pInputComponent = pInputComponent;
	m_game.GetScene()->GetCamera();
}

void SelectionSystem::Execute(double deltaTime)
{
	auto ms = m_pInputComponent->GetMouseState();

	double radius = SphericalEffect::GetRadius();
	//auto cameraPos = cameraTransform->GetSphericalPosition();

	auto w_sphere = radius - 2 * radius * pow(sin(objectRadius / radius / 2), 2);
	auto r_sphere = sqrt(radius * radius - w_sphere * w_sphere);
}