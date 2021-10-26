#pragma once
#include "Effect.h"
class SphericalEffect :
    public Effect
{
public:
    static void SetMode(bool isSpherical);
    virtual void SetRadius(double radius);
protected:
    static bool m_isSpherical;
    double m_radius;
};

