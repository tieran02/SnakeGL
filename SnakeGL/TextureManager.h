#pragma once
#include <unordered_map>
#include "Texture.h"


class TextureManager
{
public:
	TextureManager() {}

	Texture* GetTexture(char* path, char* filename, char* type);

	std::unordered_map<std::string, Texture*> TextureMap() { return this->m_textureMap; };
private:
	std::unordered_map<std::string, Texture*> m_textureMap;
};