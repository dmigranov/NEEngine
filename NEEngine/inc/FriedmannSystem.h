#pragma once
#include "ActionSystem.h"
class TransformComponent;
class SphericalRenderingComponent;
class SphericalTransformComponent;

class FriedmannSystem :
	public System
{
public:
	FriedmannSystem(SphericalTransformComponent * pTransform);
};

