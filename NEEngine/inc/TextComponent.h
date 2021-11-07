#pragma once
#include "Component.h"
class TextComponent :
    public Component
{
public:
    TextComponent(const char* m_text, const float x, const float y);
    TextComponent(std::function<char* (double delta)> func, const float x, const float y);
private:
    const char* m_text = nullptr;
    const float m_x, m_y;
    std::function<char* (double delta)> m_func;
};

