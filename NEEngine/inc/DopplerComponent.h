#pragma once
#include "Component.h"
class DopplerComponent :
    public Component
{
public:
    void SetSelected(bool isSelected);
private:
    bool m_isSelected = false;
};

