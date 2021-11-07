#pragma once
#include "Component.h"
class TextComponent :
    public Component
{
private:
    const char* m_text;
    const float m_x, m_y;
};

