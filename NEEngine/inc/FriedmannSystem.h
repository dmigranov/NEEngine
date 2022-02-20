#pragma once
#include "ActionSystem.h"
class TransformComponent;

class FriedmannSystem :
	public ActionSystem<InputComponent, TransformComponent, CameraComponent>
{
};

