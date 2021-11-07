#include "pch.h"
#include "TextPrintingSystem.h"

#include "Entity.h"
#include "TextComponent.h"
#include "TextDrawer.h"
#include "Game.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

TextPrintingSystem::TextPrintingSystem()
{
	SubscribeToComponentType<TextComponent>();

	auto& game = Game::GetInstance();
	m_textDrawer = new TextDrawer(game.GetDevice(), game.GetDeviceContext());

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

		switch (align)
		{
		case Alignment::UpRight:
			break;
		case Alignment::UpLeft:
			break;
		case Alignment::DownRight:
			break;
		case Alignment::DownLeft:
			break;

		}
	}
}

TextPrintingSystem::~TextPrintingSystem()
{
	delete m_textDrawer;
}
