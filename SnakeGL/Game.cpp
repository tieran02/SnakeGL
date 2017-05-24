#include "Game.h"
#include <GL/glew.h>
#include "ResourceManager.h"
#include <iostream>
#include <string>

float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;


Game::Game() : m_IsRunning(false), m_rotation(0.0f), score(0), m_fruitPos(0, 0), m_direction(0, 0), nTail(0), m_window(nullptr), m_shader(nullptr), m_camera(nullptr), m_headSprite(nullptr), m_fruitSprite(nullptr)
{
}


Game::~Game()
{

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
	//Snake Speed
	this->m_speed = 150.0f;
	//Create Snake Head Sprites
	this->m_headSprite = new Sprite();
	this->m_headSprite->Init("./res", "head.png", 16, 16);
	this->m_fruitSprite = new Sprite();
	this->m_fruitSprite->Init("./res", "apple.png", 16, 16);
	for (int i = 0; i < 100; i++)
	{
		this->m_tailSprites[i] = new Sprite();
		this->m_tailSprites[i]->Init("./res", "body.png", 16, 16);
	}
	nTail = 0;
	//Place Fruit
	this->m_fruitPos = glm::vec2(rand() % this->m_window->Width() , rand () % this->m_window->Height());
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

int delay = 0;
void Game::logic()
{
	//Move Snake;
	this->m_direction = glm::vec2(cos(this->m_rotation), sin(this->m_rotation));
	this->m_pos += this->m_direction * deltaTime * this->m_speed;
	//Set Snakes roation to facing direction
	this->m_headSprite->SetRotation(this->m_rotation + 1.5708);

	//Tails
	if (delay >= this->m_speed/10) {
		glm::vec2 prev = tail[0];
		glm::vec2 prev2;
		tail[0] = glm::vec2(this->m_pos.x, this->m_pos.y);
		for (int i = 1; i < nTail; i++)
		{
			prev2 = tail[i];
			tail[i] = prev;
			prev = prev2;
			delay = 0;
		}
	}
	else
		delay++;
		
	for (int i = 3; i < nTail; i++)
	{
		if (overlap(this->m_pos, tail[i], 8))
			this->m_IsRunning = false;
	}

	//TODO: Check if snake has left area
	if (this->m_pos.x > this->m_window->Width())
		this->m_pos.x = 0;
	if (this->m_pos.x < 0)
		this->m_pos.x = this->m_window->Width();

	if(this->m_pos.y > this->m_window->Height())
		this->m_pos.y = 0;
	if (this->m_pos.y < 0)
		this->m_pos.y = this->m_window->Height();

	if (overlap(this->m_pos, this->m_fruitPos,16)) {
		this->m_fruitPos = glm::vec2(rand() % this->m_window->Width(), rand() % this->m_window->Height());
		this->nTail++;
		score += 10;
		std::cout << "\nScore = " << this->score;
	}

	
}

void Game::input()
{
	SDL_Event event;

	bool left = false;
	bool right = false;
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

				case SDLK_d:
					this->m_rotation += 15.0f * deltaTime;
				break;
				case SDLK_a:
					this->m_rotation -= 15.0f * deltaTime;
				break;
			}
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

	for (int i = 0; i < nTail; i++)
	{
		m_tailSprites[i]->Draw(m_shader, this->tail[i]);
	}

	m_fruitSprite->Draw(m_shader, this->m_fruitPos);	

	this->m_shader->Unbind();
}


bool Game::overlap(glm::vec2 a, glm::vec2 b,int size)
{
	if (a.x > b.x - size && a.x < b.x + size)
		if (a.y > b.y - size && a.y < b.y + size) {
			//std::cout << "Intersected!\n";
			return true;
		}
			
	return false;
}
