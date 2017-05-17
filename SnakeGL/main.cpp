#include "Window.h"
#include "Game.h"
#include <iostream>

int main(int argc, char* argv[])
{
	Game snake;
	snake.Create(640, 360, "Snake");
	int a;
	std::cout << "\nPress any key to quit";
	std::cin >> a;
	return 0;
}
