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
	float m_rotation;
	int score;
	glm::vec2 m_fruitPos;
	glm::vec2 m_direction;
	glm::vec2 m_pos;
	glm::vec2 tail[100];
	int nTail;

	void loop();
	void logic();
	void input();
	void render();

	bool overlap(glm::vec2 a, glm::vec2 b,int size);

	//OpenGL Stuff
	Window* m_window;
	Shader* m_shader;
	Camera* m_camera;
	Sprite* m_headSprite;
	Sprite* m_fruitSprite;
	Sprite* m_tailSprites[100];
};

