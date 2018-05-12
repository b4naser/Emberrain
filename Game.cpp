#include <Windows.h>
#include <typeinfo>
#include <iostream>
#include <conio.h>
#include "Game.h"
#include "Map.h"
#include "Fight.h"
#include "Player.h"
#include "GameOver.h"

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
	Player p;
	// Inicjalizuje wszystkie Stage'e
	Map* map = new Map(&p);
	GameOver* gameOver = new GameOver();

	// Ustawia domyslny stage
	stage = map;

	// Przechowuje wpisana komende
	char cmd;

	// Pobieranie nicku gracza
	COORD cursorPos{ 30, 10 };
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 15);
	cout << "Wpisz imie bohatera:";

	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);

	std::string playerName;

	std::cin >> playerName;
	p.setPlayerName(playerName);

	system("cls");

	while(this->running)
	{
		// Wyswietla UI
		stage->show();
		
		// Czeka na wpisanie znaku
		cmd = _getch();

		//Obsluguje wpisany znak, jesli komenda nie dotyczy przelaczania interfejsow lub wyjscia przekazuje ja do aktualnego Stage'a
		if(this->gameCommandEnable && cmd == 'i')
			cout << "Inventory";
		else if (this->gameCommandEnable && cmd == 'c')
			cout << "Stats";
		else if (cmd == 'q')
			this->running = false;
		else
			stage->command(cmd);

		if (map->isDefeated())
		{
			stage = gameOver;
			this->gameCommandEnable = false;
		}
	}
}