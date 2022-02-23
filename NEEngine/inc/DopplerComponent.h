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
private:
    bool m_isSelected = false;
    bool m_isAlternative = false;
};