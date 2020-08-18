#pragma once
#include "Component.h"

class MeshComponent;
class Texture;

class BitmapComponent :
    public Component
{
public:
    struct VertexType
    {
        DirectX::SimpleMath::Vector3 position;
        DirectX::SimpleMath::Vector2 uv;
    };


    BitmapComponent(unsigned int bitmapWidth, unsigned int bitmapHeight, bool isOpaque = true);
    BitmapComponent(unsigned int bitmapWidth, unsigned int bitmapHeight, Texture * texture, bool isOpaque = true);
    
    ~BitmapComponent() override;

    void SetFrameIndex(unsigned int frameIndex);

    void SetTexture(Texture* texture);

    bool IsOpaque();

private:
    friend class BitmapRenderSystem;

    bool InitializeBuffers(ID3D11Device* device);
    void UpdateUV(VertexType*&);

    bool m_isOpaque = true;   //opaque - непрозрачный
    unsigned int m_bitmapWidth, m_bitmapHeight;
    unsigned int m_texWidth = 0, m_texHeight = 0;

    ID3D11Buffer* m_vertexBuffer = nullptr;
    ID3D11Buffer* m_indexBuffer = nullptr;
    int m_vertexCount, m_indexCount;
    Texture* m_spriteSheet;

    unsigned int m_frameIndex = 0;
};

