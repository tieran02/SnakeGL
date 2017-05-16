#include "TextureManager.h"
#include <iostream>


Texture* TextureManager::GetTexture(char* path, char* filename, char* type)
{
	//Check if texture alredy exists in texture map
	auto it = this->m_textureMap.find(filename);
	if (it == m_textureMap.end())
	{
		//Texture doesn't exist
		Texture* texture = new Texture;
		std::string file = path;
		file.append(filename);
		texture->CreateTextureFromFile(path, filename, type);
		m_textureMap.insert(std::make_pair(filename, texture));
		return this->m_textureMap[filename];
	}
	else
	{
		//Texture does exist
		std::cout << "Texture '" << filename << "' already added!";
		return this->m_textureMap[filename];
	}
}