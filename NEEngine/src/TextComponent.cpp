#include "pch.h"
#include "TextComponent.h"

TextComponent::TextComponent(const char* text, const float x, const float y) : m_x(x), m_y(y)
{
	m_func = [text](double delta) { return text; };
}

TextComponent::TextComponent(std::function<const char* (double delta)> func, const float x, const float y) : m_x(x), m_y(y)
{
	m_func = func;
}


const DirectX::SimpleMath::Vector2 TextComponent::GetPosition() const
{
	return DirectX::SimpleMath::Vector2(m_x, m_y);
}

const char* TextComponent::GetText(double delta) const
{
	return m_func(delta);
}