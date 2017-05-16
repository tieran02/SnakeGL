#include "Texture.h"
#include <string>
#include <soil.h>

Texture::Texture()
{
}

Texture::~Texture()
{

}

void Texture::Destroy()
{

}

GLuint Texture::GetTextureID()
{
	return m_texture_ID;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, this->m_texture_ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

std::string Texture::GetType()
{
	return this->type;
}

void Texture::CreateTextureFromFile(std::string directory, std::string filename, std::string type)
{
	//Generate texture ID and load texture data
	std::string file = directory + '/' + filename;
	this->type = type;
	glGenTextures(1, &this->m_texture_ID);
	unsigned char* image = SOIL_load_image(file.c_str(), &this->width, &this->height, 0, SOIL_LOAD_RGBA);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, this->m_texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}