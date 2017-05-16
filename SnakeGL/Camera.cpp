#include "Camera.h"
#include <glm/gtc/matrix_transform.inl>


Camera::Camera(int width, int height, float zoom)
{
	this->m_projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
	this->m_zoom = zoom;

	glm::vec3 camPos = glm::vec3(this->m_pos.x, this->m_pos.y, 0.0);
	this->m_view = glm::translate(m_view, camPos);
	glm::vec3 scale = glm::vec3(this->m_zoom, this->m_zoom, 1.0f);
	this->m_view = glm::scale(m_view, scale);
}

Camera::~Camera()
{
}

void Camera::Update(Shader* shader) const
{
	shader->SetUniform("projection", this->m_projection, 1, GL_FALSE);
	shader->SetUniform("view", this->m_view, 1, GL_FALSE);
}
