#pragma once
#include "Window.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Sprite.h"
#include "TextureManager.h"

class Game
{
public:
	Game();
	~Game();
	void Create(int width, int height, char* title);
private:
	bool m_IsRunning;
	glm::vec2 m_direction;
	glm::vec2 m_pos;

	void loop();
	void logic();
	void input();
	void render();

	//OpenGL Stuff
	Window* m_window;
	Shader* m_shader;
	Camera* m_camera;
	Sprite* m_headSprite;
};

