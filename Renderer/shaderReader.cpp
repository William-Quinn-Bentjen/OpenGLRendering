#include "shaderReader.h"
#include <iostream>
#include <fstream>
#include <string>
#include "render.h"

std::string* fileToString(const char* fileName)
{
	std::string* output = new std::string("");
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		printf("\n\nREADING %s\n================================================================================\n", fileName);
		while (getline(myfile, line))
		{
			output->append(line + "\n");
			std::cout << line << '\n';
		}
		myfile.close();
		printf("\n================================================================================END OF FILE\n");
	}

	else std::cout << "Unable to open file";
	return output;
	//strcpy(string, output.c_str);
	//return output.c_str;
}
//shader makeShaderFrom(std::string fileName)
//{
//	const char * vertSource = fileName.c_str + ".vert";
//	const char * fragSource = fileName.c_str + ".frag";
//	return makeShaderFrom(vertSource, fragSource);
//}
shader makeShaderFrom(const char * vertSource, const char * fragSource)
{
	const char * vertInput = fileToString(vertSource)->c_str();
	const char * fragInput = fileToString(fragSource)->c_str();
	shader newShad{};
	newShad = makeShader(vertInput, fragInput);
	//delete(vertInput);
	//delete(fragInput);
	return newShad;
}

shader makeShaderFrom(std::string vertSource, std::string fragSource)
{
	const char * vertInput = fileToString(vertSource.c_str())->c_str();
	const char * fragInput = fileToString(fragSource.c_str())->c_str();
	shader newShad{};
	newShad = makeShader(vertInput, fragInput);
	//delete(vertInput);
	//delete(fragInput);
	return newShad;
}
shader makeShaderFrom(std::string source)
{
	std::string vertInput = source + ".vert";
	std::string fragInput = source + ".frag";
	shader newShad{};
	return makeShaderFrom(vertInput, fragInput);
}
