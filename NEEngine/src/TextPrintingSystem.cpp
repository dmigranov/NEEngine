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
		auto color = pTextComponent->GetColor();

		auto& game = Game::GetInstance();
		int width, height;
		game.GetWindowSize(width, height);


		auto c_str = text.c_str();

		switch (align)
		{
		case Alignment::UpRight:
			m_textDrawer->DrawTextUpRightAlign(c_str, pos.x, pos.y, color);
			break;
		case Alignment::UpLeft:
			m_textDrawer->DrawTextUpLeftAlign(c_str, pos.x, pos.y, color);
			break;
		case Alignment::DownRight:
			m_textDrawer->DrawTextDownRightAlign(c_str, pos.x, pos.y, color);
			break;
		case Alignment::DownLeft:
			m_textDrawer->DrawTextDownLeftAlign(c_str, pos.x, pos.y, color);
			break;
		}
	}
}

TextPrintingSystem::~TextPrintingSystem()
{
	delete m_textDrawer;
}
