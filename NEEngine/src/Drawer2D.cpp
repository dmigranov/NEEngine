#include "pch.h"
#include "Drawer2D.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Drawer2D::Drawer2D(ID3D11Device* device, ID3D11DeviceContext* context)
{
    m_d3dContext = context;

    m_states = std::make_unique<CommonStates>(device);
    m_effect = std::make_unique<BasicEffect>(device);

    m_effect->SetVertexColorEnabled(true);

    void const* shaderByteCode;
    size_t byteCodeLength;

    m_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

    DX::ThrowIfFailed(
        device->CreateInputLayout(VertexPositionColor::InputElements,
            VertexPositionColor::InputElementCount,
            shaderByteCode, byteCodeLength,
            &m_inputLayout));

    m_batch = std::make_unique<PrimitiveBatch<VertexPositionColor>>(context);
}

Drawer2D::~Drawer2D()
{
    SafeRelease(m_inputLayout);
}

void Drawer2D::DrawLine(Vector2 start, Vector2 end, XMVECTORF32 color)
{
    m_d3dContext->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
    m_d3dContext->OMSetDepthStencilState(m_states->DepthNone(), 0);
    m_d3dContext->RSSetState(m_states->CullNone());

    m_effect->Apply(m_d3dContext);

    m_d3dContext->IASetInputLayout(m_inputLayout);

    m_batch->Begin();

    VertexPositionColor v1(Vector3(start.x, start.y, 0.f), color);
    VertexPositionColor v2(Vector3(end.x, end.y, 0.f), color);

    m_batch->DrawLine(v1, v2);

    m_batch->End();
}
