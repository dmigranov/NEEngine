#include "pch.h"
#include "TextComponent.h"

TextComponent::TextComponent(const char* text, const float x, const float y) : m_x(x), m_y(y), m_text(text)
{ }

TextComponent::TextComponent(std::function<char* (double delta)> func, const float x, const float y) : m_x(x), m_y(y)
{
	m_func = func;
}
