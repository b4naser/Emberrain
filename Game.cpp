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
	screenBufferSize.X = 101;
	screenBufferSize.Y = 51;

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

	this->running = true;
}

void Game::run()
{
	// Inicjalizuje wszystkie Stage'e
	Map* map = new Map(40, 40);

	// Ustawia domyslny stage
	stage = map;

	// Przechowuje Surface'a danego Stage'a
	Surface* surface;

	// Przechowuje wpisana komende
	char cmd;

	// Pozycja na ktora ustawiany jest kursor po kazdej iteracji petli while
	COORD cursorPosition{ 0, 0 };

	while(this->running)
	{
		// Zawsze przed wyswietleniem Surface'a cofa kursor do gornego lewego rogu
		SetConsoleCursorPosition(this->hConsole, cursorPosition);

		// Przepisuje wskaznik do Surface'a aktualnego Stage'a - poprawia czytelnosc ponizszej petli
		surface = stage->getSurface();

		// Wyswietla Surface'a aktualnego Stage'a
		for (int y = 0; y < surface->get().size(); y++)
		{
			for (int x = 0; x < surface->get()[0].size(); x++)
			{
				SetConsoleTextAttribute(this->hConsole, surface->get()[y][x]->getColor());
				std::cout << surface->get()[y][x]->getChar();
			}
			std::cout << std::endl;
		}

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