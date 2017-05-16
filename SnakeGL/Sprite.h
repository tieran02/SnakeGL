#pragma once
#include "glm/glm.hpp"
#include "GL/glew.h"
#include "Shader.h"

class Sprite
{
public:
	Sprite();
	~Sprite();
	void Init(char* path, char* file, int width, int height);
	void Draw(Shader* shader, glm::vec2 pos);
	void SetRotation(float rotation) { m_rotation = rotation; }
	float GetRotation() { return m_rotation; }
private:
	glm::vec2 m_pos;
	float m_scale;
	float m_rotation;
	int m_width, m_height;
	glm::mat4x4 m_model;

	GLuint m_vboID;
	GLuint m_vaoID;
	GLuint m_textureID;
};

