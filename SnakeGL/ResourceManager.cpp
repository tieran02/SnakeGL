#include "ResourceManager.h"

TextureManager* ResourceManager::textureManagerInstance = 0;


ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

TextureManager *ResourceManager::TextureManagerInstance() {
	if (textureManagerInstance == nullptr)
		textureManagerInstance = new TextureManager();

	return textureManagerInstance;
}
