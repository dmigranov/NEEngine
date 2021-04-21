#pragma once

class MeshComponent;

class MeshComponentFactory
{
public:
	template<class VertexData> MeshComponent* CreateMeshComponent(int nv, VertexData* vertices, int ni, WORD* indices) {
		MeshComponent* returnMesh = nullptr;

		//todo: создать класс CreateSphericalMeshComponent
		//его методы: создание по списку вершин и индексов,
		//но также и создание предопределнных объектов

		return returnMesh;
	}
};

