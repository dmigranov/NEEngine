#pragma once
#include "ActionSystem.h"
#include "CameraComponent.h"

class InputComponent;
class TransformComponent;


class CameraActionSystem :
	public ActionSystem<InputComponent, TransformComponent, CameraComponent>
{
public:
	CameraActionSystem();
    
};