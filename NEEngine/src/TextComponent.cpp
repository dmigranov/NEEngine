#include "pch.h"
#include "TextComponent.h"

TextComponent::TextComponent(const std::string text, const float x, const float y, Alignment align) : m_x(x), m_y(y)
{
	m_func = [text](double delta) { return text; };
	m_align = align;
}

TextComponent::TextComponent(std::function<const std::string(double delta)> func, const float x, const float y, Alignment align) : m_x(x), m_y(y)
{
	m_func = func;
	m_align = align;
}


DirectX::SimpleMath::Vector2 TextComponent::GetPosition() const
{
	return DirectX::SimpleMath::Vector2(m_x, m_y);
}

const std::string TextComponent::GetText(double delta) const
{
	return m_func(delta);
}

Alignment TextComponent::GetAlignment() const
{
	return m_align;
}
