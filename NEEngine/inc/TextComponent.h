#pragma once
#include "Component.h"
class TextComponent :
    public Component
{
public:
    TextComponent(const char* m_text, const float x, const float y);
    TextComponent(std::function<const char* (double delta)> func, const float x, const float y);

    const DirectX::SimpleMath::Vector2 GetPosition() const;
    const char* GetText(double delta = 0) const;
private:
    const char* m_text = nullptr;
    const float m_x, m_y;
    std::function<const char* (double delta)> m_func;
};

