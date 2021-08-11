#include "pch.h"
#include "HyperbolicMeshComponentFactory.h"

#include "MeshComponent.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

MeshComponent* HyperbolicMeshComponentFactory::CreateHyperbolicSphere(double radius, int sliceCount, int stackCount)
{
	int triCount = 0;

	auto phiStep = XM_PI / stackCount;
	auto thetaStep = XM_2PI / sliceCount;

	std::vector<VertexData> vertices;
	std::vector<WORD> indices;

    return nullptr;
}
