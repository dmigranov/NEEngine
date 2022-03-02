#pragma once
#include "Component.h"
class DopplerComponent :
    public Component
{
public:
    void SetSelected(bool isSelected);
    bool IsSelected();

    void SetAlternativeTexture(bool isAlternative);
    bool IsAlternativeTexture();

    void SetOldRadius(double oldRadius);
    double GetOldRadius();
private:
    bool m_isSelected = false;
    bool m_isAlternative = false;
    double m_oldRadius;
};