#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Game.h"
#include "Map.h"

using namespace std;

Game::Game()
{
	// Definicja uchwytu konsoli
	this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Coords for size of screen buffer
	COORD screenBufferSize;
	screenBufferSize.X = 80;
	screenBufferSize.Y = 30;

	// Coords for console position and size
	SMALL_RECT consoleSize;
	consoleSize.Left = 0;
	consoleSize.Top = 0;
	consoleSize.Right = screenBufferSize.X - 1;
	consoleSize.Bottom = screenBufferSize.Y - 1;

	// Error handling
	if (!SetConsoleScreenBufferSize(this->hConsole, screenBufferSize))
	{
		cout << "SetConsoleScreenBufferSize: " << GetLastError();
	}
	if (!SetConsoleWindowInfo(this->hConsole, true, &consoleSize))
	{
		cout << "SetConsoleWindowInfo: " << GetLastError();
	}

	// Ukrycie kursora konsol
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = false;
	curInfo.dwSize = 10;
	SetConsoleCursorInfo(this->hConsole, &curInfo);

	this->running = true;
}

void Game::run()
{
	// Inicjalizuje wszystkie Stage'e
	Map* map = new Map();

	// Ustawia domyslny stage
	stage = map;

	// Przechowuje wpisana komende
	char cmd;

	// Pozycja na ktora ustawiany jest kursor po kazdej iteracji petli while
	COORD cursorPosition{ 0, 0 };

	while(this->running)
	{
		// Wyswietla UI
		stage->show();

		// Czeka na wpisanie znaku
		cmd = _getch();

		//Obsluguje wpisany znak, jesli komenda nie dotyczy przelaczania interfejsow lub wyjscia przekazuje ja do aktualnego Stage'a
		switch (cmd)
		{
		case 'i':
			cout << "Inventory";
			break;
		case 'c':
			cout << "Stats";
			break;
		case 'q':
			this->running = false;
			break;
		default:
			stage->command(cmd);
			break;
		}
	}
}