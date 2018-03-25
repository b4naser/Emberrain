#include <Windows.h>
#include <iostream>
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

	//Drawing border
	/*COORD cursorPosition;
	for (int x = 0; x < screenBufferSize.X; x++)
	{
		for (int y = 0; y < screenBufferSize.Y-1; y++)
		{

			if (x == 0 || y == 0 || x == screenBufferSize.X-1 || y == screenBufferSize.Y-2)
			{
				cursorPosition.X = x;
				cursorPosition.Y = y;

				SetConsoleCursorPosition(hConsole, cursorPosition);
				cout << "#";
			}
		}
	}

	cursorPosition.X = 1;
	cursorPosition.Y = 1;
	SetConsoleCursorPosition(hConsole, cursorPosition);*/
}

void Game::run()
{

	Map map;
	stage = new Map();

	char cmd;

	COORD curPosition{ 0, 0 };
	while(this->running)
	{
		SetConsoleCursorPosition(hConsole, curPosition);

		stage->show();
		cout << endl << "What you gonna do?: ";
		cin >> cmd;

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
		}
	}
}



Game::~Game()
{
}
