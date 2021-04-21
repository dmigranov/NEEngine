#pragma once

#include "ActionSystem.h"

class InputComponent;
class SphericalTransformComponent;
class SphericalCameraComponent;



class SphericalControlSystem 
	: public ActionSystem<InputComponent, SphericalTransformComponent, SphericalCameraComponent>
{

};

