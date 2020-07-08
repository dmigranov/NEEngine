#pragma once
#include "Mesh.h"
class HyperbolicMesh :
	public Mesh
{
	HyperbolicMesh();
	HyperbolicMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices);
	HyperbolicMesh(int nv, VertexPosColor* vertices, int ni, WORD* indices, DirectX::XMMATRIX world);

	virtual void Render(std::list<DirectX::XMMATRIX> matrices) override;
	virtual void Render() override;
	virtual void Render(DirectX::XMMATRIX matrix) override;
};

