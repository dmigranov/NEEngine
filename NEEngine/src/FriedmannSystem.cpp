#include "pch.h"
#include "FriedmannSystem.h"

#include "Entity.h"
#include "SphericalTransformComponent.h"
#include "SphericalRenderingComponent.h"
#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

FriedmannSystem::FriedmannSystem(SphericalTransformComponent* pTransform)
{
	SubscribeToComponentType<SphericalTransformComponent>();
	SubscribeToComponentType<SphericalRenderingComponent>();
}

void FriedmannSystem::Execute(double deltaTime)
{
	for (auto pEntity : m_entities)
	{
		
	}
}
