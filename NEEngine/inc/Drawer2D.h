#pragma once
#include <memory>
#include "Drawer2D.h"
#include "PrimitiveBatch.h"
#include "GeometricPrimitive.h"
#include "CommonStates.h"
#include "Effects.h"

class Drawer2D
{
public:
	Drawer2D(ID3D11Device* device, ID3D11DeviceContext* context);
	~Drawer2D();
	void DrawLine(DirectX::SimpleMath::Vector2 start, DirectX::SimpleMath::Vector2 end, DirectX::XMVECTORF32 color);
private:
	ID3D11DeviceContext* m_d3dContext;
	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_batch;
	ID3D11InputLayout * m_inputLayout;
};

