#pragma once
#include <random>

#include "SphericalMesh.h"
class SphericalAsteroid :
	public SphericalMesh
{
public:
	SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color);
	SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, DirectX::XMFLOAT4 color, DirectX::XMMATRIX world);
	
	SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, Texture* texture);
	SphericalAsteroid(float amplitude, float radius, int sliceCount, int stackCount, Texture* texture, DirectX::XMMATRIX world);
private:
	std::random_device rd;
	std::mt19937 engine = std::mt19937(rd());
	std::uniform_real_distribution<> dist;

};

