#pragma once
#include "Effect.h"

enum class SphericalVisibility {
    VISIBLE_NONE,
    VISIBLE_FRONT,
    VISIBLE_BACK,   //not really necessary but why not
    VISIBLE_ALL
};

class SphericalEffect :
    public Effect
{
public:
    static void SetMode(bool isSpherical);
    static void SetRadius(double radius);
protected:
    static bool m_isSpherical;
    static double m_radius;
    static bool m_radius_set;
};

