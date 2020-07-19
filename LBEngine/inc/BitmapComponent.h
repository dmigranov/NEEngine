#pragma once
#include "Component.h"

class MeshComponent;
class Texture;

class BitmapComponent :
    public Component
{
public:
    BitmapComponent(unsigned int width, unsigned int height, bool isOpaque = true);
    BitmapComponent(unsigned int width, unsigned int height, Texture * texture, bool isOpaque = true);

    ~BitmapComponent() override;

    void SetFrameIndex(unsigned int frameIndex);

    void SetTexture(Texture* texture);

    bool IsOpaque();
private:
    bool m_isOpaque = true;   //opaque - непрозрачный
    unsigned int m_bitmapWidth, m_bitmapHeight;
    unsigned int m_texWidth = 0, m_texHeight = 0;
    MeshComponent *m_quad;

    Texture* m_spriteSheet;
    unsigned int m_frameIndex = 0;
};

