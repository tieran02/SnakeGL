#include "Window.h"
#include <GL/glew.h>
#include <cstdio>


Window::Window(int width, int height, char* title)
{
	this->m_width = width;
	this->m_height = height;
	this->m_title = title;

	SDL_Init(SDL_INIT_VIDEO);
	this->m_window = SDL_CreateWindow(this->m_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->m_width, this->m_height, SDL_WINDOW_OPENGL);

	if (this->m_window == NULL) {
		printf("Could not create window: %s\n", SDL_GetError());
	}

	// Create  opengl context
	this->m_context = SDL_GL_CreateContext(this->m_window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);


	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	Destroy();
}

void Window::Update() const
{
	SDL_GL_SwapWindow(this->m_window);
}

void Window::Destroy() const
{
	SDL_DestroyWindow(this->m_window);
}
