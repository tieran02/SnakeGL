#pragma once
#include "glm/glm.hpp"
#include "Shader.h"

class Camera
{
public:
	Camera(int width, int height, float zoom);
	~Camera();

	void Update(Shader* shader) const;
	float SetZoom(float zoom) { m_zoom = zoom; }
	glm::mat4x4 Projection() const { return m_projection; }
	glm::mat4x4 View() const { return m_view; }
private:
	float m_zoom;
	glm::vec2 m_pos;
	glm::mat4x4 m_view;
	glm::mat4x4 m_projection;
};

