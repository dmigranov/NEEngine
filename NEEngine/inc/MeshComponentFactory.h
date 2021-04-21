#pragma once

class MeshComponent;

class MeshComponentFactory
{
public:
	template<class VertexData> MeshComponent* CreateMeshComponent(int nv, VertexData* vertices, int ni, WORD* indices) {


		MeshComponent* returnMesh = new MeshComponent();
		

		//todo: создать класс SphericalMeshComponentFactory 
		//его методы: создание по списку вершин и индексов,
		//но также и создание предопределнных объектов

		return returnMesh;
	}
};

