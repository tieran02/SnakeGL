#include "Window.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Game snake;
	snake.Create(640, 360, "Snake");
	return 0;
}
