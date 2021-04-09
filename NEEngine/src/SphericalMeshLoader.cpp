#include "pch.h"
#include "SphericalMeshLoader.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

SphericalMesh* SphericalMeshLoader::LoadMesh(const char* filepath)
{
	std::ifstream infile;
	infile.open(filepath);

	if (!infile)
	{
		std::cerr << "Unable to open file " << filepath << std::endl;
		exit(1); //todo?
	}

	std::string str;

	std::vector<Mesh::VertexPosColor> vertices;
	std::vector<WORD> vertexIndices;
	
	std::vector<Vector4> positions;
	std::vector<int> positionIndices;
	std::vector<Vector2> uv0;
	std::vector<int> textureIndices;


	while (std::getline(infile, str))
	{
		if (str[0] == 'v')
		{
			if (str[1] == ' ') //v -0.5 0.5 -0.5 1
			{
				str = str.substr(2);
				std::vector<std::string> parsedStrings = parseString(str, ' ');
				std::vector<double> values = getDoubleValues(parsedStrings);
				positions.push_back(Vector4(values[0], values[1], values[2], values[3]));
			}
			else if (str[1] == 't') //vt 0 0
			{
				str = str.substr(3);
				std::vector<std::string> parsedStrings = parseString(str, ' ');
				std::vector<double> values = getDoubleValues(parsedStrings);
				uv0.push_back(Vector2(values[0], values[1]));
			}
		}
		else if (str[0] == 'f') //f 2/2 4/4 1/1
		{
			str = str.substr(2);
			std::vector<std::string> parsedStrings = parseString(str, ' ');
			for (std::string substr : parsedStrings) //2/2
			{
				std::vector<std::string> strIndices = parseString(substr, '/');
				std::vector<int> indices = getIntValues(strIndices);

				positionIndices.push_back(indices[0] - 1); //индексы считаются с единицы, а не с нуля
				textureIndices.push_back(indices[1] - 1);
			}
		}

		/*if (str.length() > 1 && str[0] == 'v' && str[1] == ' ') //v -0.5 0.5 -0.5
		{

			str = str.substr(2);
			std::vector<std::string> parsedStrings = parseString(str, ' ');
			std::vector<double> values = getDoubleValues(parsedStrings);
			vertices.push_back({ XMFLOAT4(values[0], values[1], values[2], values[3]), XMFLOAT4(values[4], values[5], values[6], 1.f) });
		}

		else if (str.length() > 1 && str[0] == 'i' && str[1] == ' ') //i 1 2 3
		{

			str = str.substr(2);
			std::vector<std::string> strIndices = parseString(str, ' ');
			std::vector<int> triangleIndices = getIntValues(strIndices);			
			vertexIndices.insert(std::end(vertexIndices), std::begin(triangleIndices), std::end(triangleIndices));
		}*/
	}

	for (int i = 0; i < positionIndices.size(); i++)
	{
		auto posIndex = positionIndices[i];
		auto texIndex = textureIndices[i];

		Mesh::VertexPosColor vpc = { positions[posIndex], XMFLOAT4(1.f, 1.f, 1.f, 1.f), uv0[texIndex] };
		vertices.push_back(vpc);
		vertexIndices.push_back(i);
	}

	return new SphericalMesh(vertices.size(), &vertices[0], vertexIndices.size(), &vertexIndices[0]);
}

std::vector<std::string> SphericalMeshLoader::parseString(std::string str, char delimiter)
{
	std::vector<std::string> vec;
	size_t startIndex = 0;
	size_t endIndex;
	while ((endIndex = str.find(delimiter, startIndex)) != std::string::npos)
	{
		std::string substr = str.substr(startIndex, endIndex - startIndex);
		vec.push_back(substr);
		startIndex = endIndex + 1;
	}
	std::string substr = str.substr(startIndex, endIndex - startIndex);
	vec.push_back(substr);
	return vec;
}

std::vector<double> SphericalMeshLoader::getDoubleValues(std::vector<std::string> strings)
{
	std::vector<double> vec;
	for (std::string str : strings)
	{
		vec.push_back(atof(str.c_str()));
	}
	return vec;
}

std::vector<int> SphericalMeshLoader::getIntValues(std::vector<std::string> strings)
{
	std::vector<int> vec;
	for (std::string str : strings)
	{
		vec.push_back(atoi(str.c_str()));
	}
	return vec;
}
