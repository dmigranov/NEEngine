#pragma once

class VertexTexMeshComponent;

class MeshLoader
{
	static VertexTexMeshComponent* LoadMesh(const char* filepath);
private:
	static std::vector<std::string> parseString(std::string str, char delimiter);
	static std::vector<double> getDoubleValues(std::vector<std::string> strings);
	static std::vector<int> getIntValues(std::vector<std::string> strings);

};

