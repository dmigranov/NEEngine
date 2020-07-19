#include "pch.h"
#include "BitmapComponent.h"

#include "MeshComponent.h"

BitmapComponent::BitmapComponent(unsigned int width, unsigned int height)
{
	//todo
	m_quad = new MeshComponent(4, nullptr, 6, nullptr);
	m_bitmapWidth = width;
	m_bitmapHeight = height;
}

BitmapComponent::~BitmapComponent()
{
}

void BitmapComponent::SetFrameIndex(unsigned int frameIndex)
{
	m_frameIndex = frameIndex;
}
