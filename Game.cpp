#include <Windows.h>
#include <typeinfo>
#include <iostream>
#include <conio.h>
#include "Game.h"
#include "Map.h"
#include "Equipment.h"
#include "Fight.h"
#include "Player.h"
#include "GameOver.h"
#include <random>

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
	COORD cursorPos;

	Player p;

	// Inicjalizuje wszystkie Stage'e
	Map* map = new Map(&p);
	Equipment* equipment = p.eq;
	GameOver* gameOver = new GameOver();

	// Ustawia domyslny stage
	stage = map;

	// Przechowuje wpisana komende
	char cmd;

	// Wyswietlenie tytulu
	cursorPos.X = 9;
	cursorPos.Y = 5;

	string titleText[6] = {
		"___________      ___                                __        ",
		"\\_   _____/ _____\\_ |__   _______________________  |__| ____  ",
		" |    __)_ /     \\| __ \\_/ __ \\_  __ \\_  __ \\__  \\ |  |/    \\ ",
		" |        \\  Y Y  \\ \\_\\ \\  ___/|  | \\/|  | \\// __ \\|  |   |  \\",
		"/_______  /__|_|  /___  /\\___  >__|   |__|  (____  /__|___|  /",
		"        \\/      \\/    \\/     \\/                  \\/        \\/ "
	};

	SetConsoleTextAttribute(hConsole, 5);
	for (int i = 0; i < 6; i++)
	{
		SetConsoleCursorPosition(hConsole, cursorPos);
		std::cout << titleText[i];
		cursorPos.Y += 1;
	}

	// Pobieranie nicku gracza
	cursorPos.X = 30;
	cursorPos.Y = 15;
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
		p.refreshPlayer();

		// Wyswietla UI
		stage->show();
		
		// Czeka na wpisanie znaku
		cmd = _getch();

		//Obsluguje wpisany znak, jesli komenda nie dotyczy przelaczania interfejsow lub wyjscia przekazuje ja do aktualnego Stage'a
		if (this->gameCommandEnable && cmd == 'i')
		{
			SetConsoleTextAttribute(hConsole, 15);
			system("cls");
			stage = equipment;
		}
		else if (this->gameCommandEnable && cmd == 'm')
		{
			SetConsoleTextAttribute(hConsole, 15);
			system("cls");
			stage = map;
		}
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