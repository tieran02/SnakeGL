#include "Sprite.h"
#include <glm/gtc/matrix_transform.inl>
#include "ResourceManager.h"
#include <iostream>

Sprite::Sprite(): m_pos(0, 0), m_scale(0), m_rotation(0), m_width(0), m_height(0), m_vboID(0), m_vaoID(0), m_textureID(0)
{
}

Sprite::~Sprite()
{
	if(this->m_vboID != 0)
	{
		glDeleteBuffers(1, &this->m_vboID);
	}
}

void Sprite::Init(char* path, char* file, int width, int height)
{
	this->m_width = width;
	this->m_height = height;

	this->m_textureID = ResourceManager::TextureManagerInstance()->GetTexture(path, file, "texture_diffuse")->GetTextureID();

	GLfloat vertices[] = {
		// First triangle
		1.0f,  1.0, 0.0f,	1.0f, 1.0f,  // Top Right
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f, // Bottom Right
		-1.0f,  1.0, 0.0f,  0.0f, 1.0f,// Top Left 
		// Second triangle
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f,// Bottom Right
		-1.0f, -1.0, 0.0f,  0.0f, 0.0f,// Bottom Left
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f // Top Left
	};

	glGenVertexArrays(1, &this->m_vaoID);
	glGenBuffers(1, &this->m_vboID);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->m_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, this->m_vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Vertex Texture2D Coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
}

void Sprite::Draw(Shader* shader, glm::vec2 pos)
{
	this->m_pos = pos;
	this->m_model = glm::mat4x4();
	this->m_model = glm::translate(this->m_model, glm::vec3(this->m_pos.x, this->m_pos.y, 0));
	this->m_model = glm::rotate(this->m_model, this->m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::vec3 scale = glm::vec3(this->m_width, this->m_height, 1);
	this->m_model = glm::scale(this->m_model, scale);

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader->GetProgramID(), "ourTexture"), 0);
	glBindTexture(GL_TEXTURE_2D, this->m_textureID);
	glActiveTexture(GL_TEXTURE0);

	shader->SetUniform("model", this->m_model, 1, GL_FALSE);

	glBindVertexArray(this->m_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 6); // We set the count to 6 since we're drawing 6 vertices now (2 triangles); not 3!
	glBindVertexArray(0);
}
