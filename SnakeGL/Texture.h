#pragma once
#include <GL/glew.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	void Destroy();
	void Bind();
	void Unbind();
	void CreateTextureFromFile(std::string directory, std::string filename, std::string type);
	GLuint GetTextureID();
	std::string GetType();
private:
	GLuint m_texture_ID;
	int width;
	int height;
	std::string type;
};

