#include "Window.h"
#include "Game.h"
#include <iostream>
#include <string>

bool menu();
char input;

int main(int argc, char* argv[])
{
	while (true)
	{
		if (!menu()) {
			break;
		}
	}
	std::cout << "\nPress any key to quit";

	std::cin >> input;
	return 0;
}

bool menu()
{
	std::cout << "Press 'P' to play the game\n";
	std::cout << "Prsss 'I' to display user guide\n";
	std::cout << "Prsss 'Q' to quit the game\n";
	std::cin >> input;
	system("cls");


	if (input == 'P' || input == 'p')
	{
		Game snake;
		snake.Create(640, 360, "Snake");
		return false;
	}
	else if (input == 'I' || input == 'i')
	{
		std::cout << "----------------------User Guide----------------------\n\n";

		std::cout << "-----------------------Controls-----------------------\n";
		std::cout << "A - Rotate Left\n";
		std::cout << "D - Roatate Right\n";
		std::cout << "Escape - Quit Game\n";
		std::cout << "------------------------------------------------------\n\n";

		std::cout << "----------------------Objective-----------------------\n";
		std::cout << "- Navigate across the screen to collect the fruit.\n";
		std::cout << "- Once you collect a fruit your tail will grow.\n";
		std::cout << "- Be carefull not to eat your own tail or its gameover!\n";
		std::cout << "------------------------------------------------------\n\n";


		std::cout << "-------------------Restart Game:----------------------\n";
		std::cout << "1 - Quit and close the game\n";
		std::cout << "2 - Execute the snake game again and play the game\n";
		std::cout << "------------------------------------------------------\n\n";


		std::cout << "\n\nEnter any key to continue\n";
		std::cin >> input;
	}
	else if (input == 'Q' || input == 'q') {
		return false;
	}
	system("cls");
	return true;
}
