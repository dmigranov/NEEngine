#pragma once

class MeshComponent;

class MeshComponentFactory
{
public:
	template<class VertexData> MeshComponent* CreateMeshComponent(int nv, VertexData* vertices, int ni, WORD* indices) {
		//todo: создание и возвращение MeshComponent


		return nullptr;
	}
};

