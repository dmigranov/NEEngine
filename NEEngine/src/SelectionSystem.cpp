#include "SelectionSystem.h"

#include "SphericalTransformComponent.h"
#include "SphericalRenderingComponent.h"
#include "InputComponent.h"


SelectionSystem::SelectionSystem(InputComponent* pInputComponent)
{
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<SphericalRenderingComponent>();

	m_pInputComponent = pInputComponent;
}

void SelectionSystem::Execute(double deltaTime)
{

}
