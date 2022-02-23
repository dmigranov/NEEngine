#pragma once
#include "Component.h"
class DopplerComponent :
    public Component
{
public:
    void SetSelected(bool isSelected);
    bool IsSelected();
    bool SetAlternativeTexture(bool isAlternative);
private:
    bool m_isSelected = false;
    bool m_isAlternative = false;
};