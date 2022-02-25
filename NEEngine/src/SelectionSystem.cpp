#include "SelectionSystem.h"

#include "SphericalTransformComponent.h"
#include "SphericalRenderingComponent.h"

SelectionSystem::SelectionSystem()
{
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<SphericalRenderingComponent>();
}

void SelectionSystem::Execute(double deltaTime)
{
}
