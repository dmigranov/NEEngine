#include "pch.h"
#include "FriedmannSystem.h"

#include "Entity.h"
#include "SphericalTransformComponent.h"
#include "SphericalRenderingComponent.h"
#include "SphericalMath.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


FriedmannSystem::FriedmannSystem(SphericalTransformComponent * pTransform) : ActionSystem([pTransform](Entity* pEntity, double deltaTime) {
    auto cameraPos = pTransform->GetSphericalPosition();
    
    auto pTransform = pEntity->GetComponent<SphericalTransformComponent>();
    auto pos = pTransform->GetSphericalPosition();
    auto renderingComponent = pEntity->GetComponent<SphericalRenderingComponent>();
    auto visibility = renderingComponent->GetSphericalVisibility();

    auto dist = SphericalDistance(pos / radius, cameraPos / radius, 1.);

    if (mu < dist)
        renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_NONE);
    else if (mu >= dist && mu <= (2 * XM_PI - dist))
        renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_FRONT);
    else //mu > (2 * XM_PI - dist)
        renderingComponent->SetSphericalVisibility(SphericalVisibility::VISIBLE_ALL);
	
	})
{	}
