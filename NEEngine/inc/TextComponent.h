#pragma once
#include "Component.h"

enum class Alignment {
    UpRight,
    UpLeft,
    DownRight,
    DownLeft
};


class TextComponent :
    public Component
{
public:
    TextComponent(const std::string m_text, const float x, const float y, Alignment align);
    TextComponent(std::function<const std::string (double delta)> func, const float x, const float y, Alignment align);

    DirectX::SimpleMath::Vector2 GetPosition() const;
    const std::string GetText(double delta = 0) const;
    Alignment GetAlignment() const;
private:
    const std::string m_text;
    const float m_x, m_y;
    std::function<const std::string(double delta)> m_func;
    Alignment m_align;
};

