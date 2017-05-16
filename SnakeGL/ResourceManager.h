#pragma once
#include "TextureManager.h"

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	static TextureManager* TextureManagerInstance();
private:
	static TextureManager* textureManagerInstance;
};
