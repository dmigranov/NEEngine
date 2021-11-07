#include "pch.h"
#include "TextPrintingSystem.h"

#include "TextComponent.h"
#include "TextDrawer.h"

TextPrintingSystem::TextPrintingSystem()
{
	SubscribeToComponentType<TextComponent>();

	m_isDrawing = true;
}

void TextPrintingSystem::Execute(double deltaTime)
{
}
