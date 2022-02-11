#pragma once
#include "Component.h"

enum class SphericalVisibility {
	VISIBLE_NONE,
	VISIBLE_FRONT,
	VISIBLE_BACK,           //not really necessary but why not
	VISIBLE_ALL
};

class SphericalRenderingComponent :
    public Component
{
};

