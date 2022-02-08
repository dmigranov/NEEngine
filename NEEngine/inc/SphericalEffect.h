#pragma once
#include "Effect.h"
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

