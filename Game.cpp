#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Game.h"
#include "Map.h"

using namespace std;

Game::Game()
{
	// Definicja uchwytu konsoli
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Coords for size of screen buffer
	COORD screenBufferSize;
	screenBufferSize.X = 100;
	screenBufferSize.Y = 50;

	// Coords for console position and size
	SMALL_RECT consoleSize;
	consoleSize.Left = 0;
	consoleSize.Top = 0;
	consoleSize.Right = screenBufferSize.X - 1;
	consoleSize.Bottom = screenBufferSize.Y - 1;

	// Error handling
	if (!SetConsoleScreenBufferSize(hConsole, screenBufferSize))
	{
		cout << "SetConsoleScreenBufferSize: " << GetLastError();
	}
	if (!SetConsoleWindowInfo(hConsole, true, &consoleSize))
	{
		cout << "SetConsoleWindowInfo: " << GetLastError();
	}

	this->running = true;

	gameSurface = new Surface(70, 40);

	//Drawing border
	for (int x = 0; x < screenBufferSize.X; x++)
	{
		for (int y = 0; y < screenBufferSize.Y; y++)
		{

			if (x == 0 || y == 0 || x == consoleSize.Right || y == consoleSize.Bottom)
			{
				this->gameSurface->printAt("#", 175, y, x);
			}
		}
	}
}

void Game::run()
{
	stage = new Map(70, 40);

	this->gameSurface->print();

	char cmd;

	COORD curPosition{ 0, 0 };
	while(this->running)
	{
		SetConsoleCursorPosition(hConsole, curPosition);

		stage->show();
		cmd = _getch();

		//Handling main commands like changing stage itd or pass it to current stage
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



Game::~Game()
{
}
