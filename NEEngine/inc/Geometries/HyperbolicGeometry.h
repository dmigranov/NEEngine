#pragma once

// Common

#include <pch.h>

#include "Game.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "InputComponent.h"
#include "Entity.h"

// Math

#include "SphericalMath.h" //todo: remove - should be in TransformComponent instead

// Components

#include "ComponentTypeManager.h"

#include "MeshComponent.h"
#include "HyperbolicTransformComponent.h"
//#include "HyperbolicCameraComponent.h"
//#include "HyperbolicMeshComponentFactory.h"

// Systems

#include "HyperbolicRenderSystem.h"
//#include "HyperbolicControlSystem.h"

// Effects

#include "HyperbolicExpFogEffect.h"