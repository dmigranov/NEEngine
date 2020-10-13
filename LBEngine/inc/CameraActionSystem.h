#pragma once
#include "ActionSystem.h"

class InputComponent;
class TransformComponent;
class WalkComponent;
class PhysicsComponent;

class CameraActionSystem :
	public ActionSystem<InputComponent, TransformComponent, WalkComponent, PhysicsComponent>
{
public:
	CameraActionSystem();
};