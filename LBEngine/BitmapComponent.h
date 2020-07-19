#pragma once
#include "Component.h"
class MeshComponent;

class BitmapComponent :
    public Component
{
public:
    BitmapComponent();
    ~BitmapComponent() override;
private:
    bool isOpaque = true;   //opaque - непрозрачный
    int m_bitmapWidth, m_bitmapHeight;
    MeshComponent *m_quad;
};

