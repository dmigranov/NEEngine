#pragma once
#include "Component.h"

enum class SphericalVisibility {
	VISIBLE_NONE,
	VISIBLE_FRONT,
	//VISIBLE_BACK,           //not really necessary
	VISIBLE_ALL
};

class SphericalRenderingComponent :
    public Component
{
public:
	SphericalVisibility GetSphericalVisibility();
	void SetSphericalVisibility(SphericalVisibility sphVisibility);
private:
	SphericalVisibility m_sphericalVisibility = SphericalVisibility::VISIBLE_ALL;
};