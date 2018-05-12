#include <iostream>
#include <Windows.h>
#include <string>
#include "GameOver.h"

void GameOver::show()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { 4, 10 };

	SetConsoleTextAttribute(hConsole, 12);
	system("cls");

	std::string gameOverText[6] = {
		"  ___   ________                      ________                      ___  ",
		" / /   /  _____/_____    _____   ____ \\_____  \\___  __ ___________   \\ \\ ",
		" \\ \\  /   \\  ___\\__  \\  /     \\_/ __ \\ /   |   \\  \\/ // __ \\_  __ \\  / / ",
		" < <  \\    \\_\\  \\/ __ \\|  | |  \\  ___//    |    \\   /\\  ___/|  | \\/  > > ",
		" / /   \\______  (____  /__|_|  /\\___  >_______  /\\_/  \\___  >__|     \\ \\ ",
		" \\_\\_         \\/     \\/      \\/     \\/        \\/          \\/        _/_/ "
	};

	for (int i = 0; i < 6; i++)
	{
		SetConsoleCursorPosition(hConsole, cursorPos);
		std::cout << gameOverText[i];
		cursorPos.Y += 1;
	}

	cursorPos.X = 35;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << "Press q to exit";
}

void GameOver::command(char cmd)
{

}