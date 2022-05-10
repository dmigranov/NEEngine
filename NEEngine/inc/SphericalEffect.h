#pragma once
#include "Effect.h"

class SphericalEffect :
    public Effect
{
public:
    static void SetMode(bool isSpherical);
    static bool GetMode();

    static void SetRadius(double radius);
    static double GetRadius();
protected:
    static bool m_isSpherical;
    static double m_radius;
    static bool m_radius_set;
};

