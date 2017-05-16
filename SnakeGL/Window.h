#pragma once
#include <SDL.h>

class Window
{
public:
	Window(int width, int height, char* title);
	~Window();
	void Update() const;
	void Destroy() const;
	int Width() const { return m_width; }
	int Height() const { return m_height; }
private:
	int m_width;
	int m_height;
	char* m_title;
	SDL_Window* m_window;
	SDL_GLContext m_context;
};

