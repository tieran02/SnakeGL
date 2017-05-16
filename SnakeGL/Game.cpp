#include "Game.h"
#include <GL/glew.h>
#include "ResourceManager.h"

float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;

Game::Game(): m_IsRunning(false), m_direction(1,0), m_window(nullptr), m_shader(nullptr), m_camera(nullptr), m_headSprite(nullptr)
{
}


Game::~Game()
{
	this->m_window->Destroy();
}

void Game::Create(int width, int height, char* title)
{
	this->m_window = new Window(width, height, title);
	this->m_IsRunning = true;

	//Compile Shader
	this->m_shader = new Shader();
	this->m_shader->CompileFromFile("./res/shader.vert", "./res/shader.frag");
	//Create Camera
	float zoom = 1;
	this->m_camera = new Camera(width, height,zoom);
	//Set Snakes Position
	this->m_pos = glm::vec2(width / 2, height / 2);
	//Create Snake Head Sprites
	this->m_headSprite = new Sprite();
	m_headSprite->Init("./res", "head.png", 16, 16);

	loop();
}


void Game::loop()
{
	while (this->m_IsRunning)
	{
		m_window->Update();
		thisTime = SDL_GetTicks();
		deltaTime = (float)(thisTime - lastTime) / 1000;
		lastTime = thisTime;

		input();
		logic();
		render();
	}
}

void Game::logic()
{
	//Move Snake;
	if(this->m_direction != glm::vec2(0,0))
		this->m_direction = glm::normalize(this->m_direction);
	this->m_pos += this->m_direction * deltaTime * 60.0f;
	//Set Snakes roation to facing direction
	this->m_headSprite->SetRotation(std::atan2(this->m_direction.x, -this->m_direction.y));

	//TODO: Check if snake has left area
	
}

void Game::input()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//Quit game is the user closes window
			case SDL_QUIT:
				this->m_IsRunning = false;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						this->m_IsRunning = false;
					break;
				}
		default:
			break;
		}
	}
}

void Game::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->m_shader->Bind();
	this->m_camera->Update(this->m_shader);
	//Render Code here
	m_headSprite->Draw(m_shader, this->m_pos);
	this->m_shader->Unbind();
}
