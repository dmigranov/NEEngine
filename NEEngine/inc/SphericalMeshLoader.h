#pragma once
#include "SphericalMesh.h"

class SphericalMeshLoader
{
public:
	static SphericalMesh* LoadMesh(const char* filepath);
private:
	static std::vector<std::string> parseString(std::string str, char delimiter);
	static std::vector<double> getDoubleValues(std::vector<std::string> strings);
	static std::vector<int> getIntValues(std::vector<std::string> strings);

};

