#pragma once
#include "Component.h"
class DopplerComponent :
    public Component
{
public:
    void SetSelected(bool isSelected);
    bool IsSelected();
private:
    bool m_isSelected = false;
};