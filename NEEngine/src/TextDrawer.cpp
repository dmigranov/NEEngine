#include "pch.h"
#include "TextDrawer.h"
#include "font.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


TextDrawer::TextDrawer(ID3D11Device* device, ID3D11DeviceContext *context)
{
	m_spriteBatch = std::make_unique<SpriteBatch>(context);
	m_font = std::make_unique<SpriteFont>(device, myfile_spritefont, sizeof(myfile_spritefont) / sizeof(unsigned char));
}

void TextDrawer::DrawTextUpRightAlign(const char* output, float x, float y, DirectX::XMVECTOR color)
{
	m_spriteBatch->Begin();

	Vector2 pos = Vector2(x, y);
	Vector2 origin = m_font->MeasureString(output)/* / 2.f*/;
	origin.y = 0;
	m_font->DrawString(m_spriteBatch.get(), output,
		pos, color, 0.f, origin);

	m_spriteBatch->End();
}

void TextDrawer::DrawTextUpLeftAlign(const char* output, float x, float y, DirectX::XMVECTOR color)
{
	m_spriteBatch->Begin();

	Vector2 pos = Vector2(x, y);
	Vector2 origin(0.f, 0.f); // = m_font->MeasureString(output);
	m_font->DrawString(m_spriteBatch.get(), output,
		pos, color, 0.f, origin);

	m_spriteBatch->End();
}

void TextDrawer::DrawTextDownLeftAlign(const char* output, float x, float y, DirectX::XMVECTOR color)
{
	m_spriteBatch->Begin();

	Vector2 pos = Vector2(x, y);
	Vector2 origin = m_font->MeasureString(output);
	origin.x = 0;
	m_font->DrawString(m_spriteBatch.get(), output,
		pos, color, 0.f, origin);

	m_spriteBatch->End();
}

void TextDrawer::DrawTextDownRightAlign(const char* output, float x, float y, DirectX::XMVECTOR color)
{
	m_spriteBatch->Begin();

	Vector2 pos = Vector2(x, y);
	Vector2 origin = m_font->MeasureString(output);
	m_font->DrawString(m_spriteBatch.get(), output,
		pos, color, 0.f, origin);

	m_spriteBatch->End();
}
