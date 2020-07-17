#include "pch.h"
#include "MeshLoader.h"
#include "..\inc\MeshLoader.h"

MeshComponent* MeshLoader::LoadMesh(const char* filepath)
{
	std::ifstream infile;
	infile.open(filepath);

	if (!infile)
	{
		std::cerr << "Unable to open file " << filepath << std::endl;
		exit(1); //todo?
	}

	std::string str;

	while (std::getline(infile, str))
	{
		if (str[0] == 'v')
		{
			if (str[1] == ' ') //v -0.5 0.5 -0.5 1
			{
				
			}
			else if (str[1] == 't') //vt 0 0
			{
				
			}
		}
		else if (str[0] == 'f') //f 2/2 4/4 1/1
		{
			str = str.substr(2);
			std::vector<std::string> parsedStrings = parseString(str, ' ');
			for (std::string substr : parsedStrings) //2/2
			{
				
			}
		}

		if (str.length() > 1 && str[0] == 'v' && str[1] == ' ') //v -0.5 0.5 -0.5
		{

		}

		else if (str.length() > 1 && str[0] == 'i' && str[1] == ' ') //i 1 2 3
		{

		}
	}

	return nullptr;
}
