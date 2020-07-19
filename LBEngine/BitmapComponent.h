#pragma once
#include "Component.h"
class MeshComponent;

class BitmapComponent :
    public Component
{
public:
    BitmapComponent(unsigned int width, unsigned int height);
    BitmapComponent(unsigned int width, unsigned int height, Texture * texture);

    ~BitmapComponent() override;

    void SetFrameIndex(unsigned int frameIndex);
private:
    bool isOpaque = true;   //opaque - непрозрачный
    unsigned int m_bitmapWidth, m_bitmapHeight;
    unsigned int m_texWidth, m_texHeight;
    MeshComponent *m_quad;
    Texture* spriteSheet;

    unsigned int m_frameIndex;
};

