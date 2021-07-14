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
#include "SphericalTransformComponent.h"
#include "SphericalCameraComponent.h"
#include "SphericalMeshComponentFactory.h"

// Systems
#include "SphericalRenderSystem.h"
#include "SphericalControlSystem.h"

// Effects
#include "SphericalExpFogEffect.h"