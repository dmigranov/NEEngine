#pragma once

// Common

#include <pch.h>

#include "Game.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "InputComponent.h"
#include "Entity.h"

// Components

#include "ComponentTypeManager.h"

#include "MeshComponent.h"
#include "CameraComponent.h"
#include "ToricTransformComponent.h"

#include "EuclideanMeshComponentFactory.h"

// Systems
#include "ToricRenderSystem.h"
#include "ToricControlSystem.h"

// Effects
#include "ToricExpFogEffect.h"

//todo: вынести в функцию в заголовке пространства для RegisterComponentType всего нужного!