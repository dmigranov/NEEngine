#pragma once
#include "ActionSystem.h"
class TransformComponent;
class SphericalRenderingComponent;
class SphericalTransformComponent;

class FriedmannSystem :
	public ActionSystem<SphericalTransformComponent, TransformComponent, SphericalRenderingComponent>
{
public:
	FriedmannSystem();
};

