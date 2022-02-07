#pragma once
#include <SpriteBatch.h>
#include <SpriteFont.h>


class TextDrawer
{
public:
	TextDrawer(ID3D11Device* device, ID3D11DeviceContext* context);
	void DrawTextUpRightAlign(const char* output, float x, float y, DirectX::XMVECTOR color);
	void DrawTextUpLeftAlign(const char* output, float x, float y, DirectX::XMVECTOR color);
	void DrawTextDownLeftAlign(const char* output, float x, float y, DirectX::XMVECTOR color);
	void DrawTextDownRightAlign(const char* output, float x, float y, DirectX::XMVECTOR color);


private:
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
	std::unique_ptr<DirectX::SpriteFont> m_font;
};

