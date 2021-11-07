#include "pch.h"
#include "TextPrintingSystem.h"

#include "Entity.h"
#include "TextComponent.h"
#include "TextDrawer.h"

TextPrintingSystem::TextPrintingSystem()
{
	SubscribeToComponentType<TextComponent>();

	m_isDrawing = true;
}

void TextPrintingSystem::Execute(double deltaTime)
{
	for (auto pEntity : m_entities)
	{
		auto * pTextComponent = pEntity->GetComponent<TextComponent>();
		auto align = pTextComponent->GetAlignment();
		auto text = pTextComponent->GetText(deltaTime);
		auto pos = pTextComponent->GetPosition();
	}
}
