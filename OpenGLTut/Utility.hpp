#pragma once

#include<string>
#include <fstream>
#include <iostream>

 class Utility
{
public:
	static std::string GetStringFromFile(const char* fileName)
	{
		std::string returnString;
		std::ifstream file(fileName, std::ios::in);
		if (!file.good()) 
		{ 
			std::cout << "Can't read file " << fileName << std::endl; 
			std::terminate();
		} 
		file.seekg(0, std::ios::end); 
		returnString.resize((unsigned int)file.tellg());
		file.seekg(0, std::ios::beg); 
		file.read(&returnString[0], returnString.size());
		file.close(); 
		return returnString;
	}

	static unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);



 };
