#include "pch.h"
#include "BitmapComponent.h"

#include "MeshComponent.h"

BitmapComponent::BitmapComponent(unsigned int width, unsigned int height)
{
	//todo
	m_quad = new MeshComponent(4, nullptr, 6, nullptr);
	m_bitmapWidth = width;
	m_bitmapHeight = height;
	m_spriteSheet = nullptr;
}

BitmapComponent::BitmapComponent(unsigned int width, unsigned int height, Texture* texture) : BitmapComponent(width, height)
{
	m_spriteSheet = texture;
	m_texWidth = texture->GetWidth();
	m_texWidth = texture->GetHeight();
}

BitmapComponent::~BitmapComponent()
{
	delete m_quad;
}

void BitmapComponent::SetFrameIndex(unsigned int frameIndex)
{
	m_frameIndex = frameIndex;
}
