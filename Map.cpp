#include <iostream>
#include <Windows.h>
#include <vector>
#include "Map.h"

#include <typeinfo>

using namespace std;

COORD mapPosition{ 0, 0 };
COORD mapPrintSize{ 7, 5 }; // Niezale¿nie od podania liczby parzystej czy nieparzystej znak gracza zawsze bêdzie na œrodku. W przypadku podania parzystej rozmiar zostanie zwiêkszony o 1

Map::Map()
{
	// Powiêksza wektor mapy
	this->map.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));

	// Generowanie mapy
	RandomMap rm(this->MAP_WIDTH, this->MAP_HEIGHT);
	rm.generateMap();

	// Przepisanie randomowej mapy
	this->map = rm.getMap();

	// Wylosowanie pozycji portalu, gracza i przeciwnikow
	this->generatePos();
}

void Map::show()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos;

	for (int x = 50; x < 70; x++)
	{
		for (int y = 5; y < 10; y++)
		{
			cursorPos.X = x;
			cursorPos.Y = y;
			SetConsoleCursorPosition(hConsole, cursorPos);
			SetConsoleTextAttribute(hConsole, 0);
			cout << " ";
		}
	}

	for (int x = 2; x < this->MAP_WIDTH+2; x++)
	{
		for (int y = 2; y < this->MAP_HEIGHT+2; y++)
		{
			cursorPos.X = x;
			cursorPos.Y = y;
			SetConsoleCursorPosition(hConsole, cursorPos);

			//// Wyswietlenie playera
			if (this->playerPos.x+2 == x && this->playerPos.y+2 == y)
			{
				SetConsoleTextAttribute(hConsole, 47);
				cout << "@";
				goto cntn; // Pomija wyswietlanie reszty elementow
			}

			// Wyswietlenie portalu
			if (this->portalPos.x + 2 == x && this->portalPos.y + 2 == y)
			{
				SetConsoleTextAttribute(hConsole, 109);
				cout << char(177);
				goto cntn; // Pomija wyswietlanie reszty elementow
			}

			for (int k = 0; k < this->enemies.size(); k++)
			{
				if (this->enemies[k][1]+2 == y && this->enemies[k][0]+2 == x)
				{
					// Dostosowuje kolor na podstawie typu przeciwnika
					switch (this->enemies[k][2])
					{
					case 1:
						SetConsoleTextAttribute(hConsole, 41);
						cout << char(2);
						break;
					case 2:
						SetConsoleTextAttribute(hConsole, 43);
						cout << char(2);
						break;
					case 3:
						SetConsoleTextAttribute(hConsole, 46);
						cout << char(2);
						break;
					}

					goto cntn;
				}
			}

			// Wyswietlenie terenu wzgledem liczby z tablicy map
			switch (this->map[y-2][x-2])
			{
			case 0:
				SetConsoleTextAttribute(hConsole, 98);
				cout << char(178);
				break;
			case 1:
				SetConsoleTextAttribute(hConsole, 136);
				cout << char(219);
				break;
			case 2:
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(176);
				break;
			case 3:
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(177);
				break;
			case 4:
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(178);
				break;
			}

		cntn:; // Bez tego goto nie dziala, ale rownie dobrze moze byc tu cokolwiek tylko nie }
		}

		// Sprawdzanie czy jakis przeciwnik znajduje sie w zasiegu
		// TODO: uzycie wartosci bezwzglednej roznicy pozycji zamiast iterowania po kazdej pozycji wokol gracza

		this->target = -1; // Sluzy do przechowywania celu ktory ma zostac zaatakowany, gdy przeciwnik jest w poblizu ustawia wartosc na index przeciwnika w tablicy
		for (int y = this->playerPos.y - 1; y < this->playerPos.y + 2; y++)
		{
			for (int x = this->playerPos.x - 1; x < this->playerPos.x + 2; x++)
			{
				// Czy jest jakis przeciwnik?
				for (int k = 0; k < this->enemies.size(); k++)
				{
					if (this->enemies[k][1] == y && this->enemies[k][0] == x)
					{
						cursorPos.X = 50;
						cursorPos.Y = 5;
						SetConsoleCursorPosition(hConsole, cursorPos);
						SetConsoleTextAttribute(hConsole, 15);
						cout << "z - zaatakuj " << enemies[k][2];
						target = k;
						goto finish;
					}
				}
			}
			finish:;
		}

		// Sprawdzanie czy gracz znajduje sie na portalu
		if (playerPos.x == portalPos.x && playerPos.y == portalPos.y)
		{
			cursorPos.X = 50;
			cursorPos.Y = 6;
			SetConsoleCursorPosition(hConsole, cursorPos);
			SetConsoleTextAttribute(hConsole, 15);
			cout << "g - zejdz nizej";
		}
	}
}

void Map::command(char cmd)
{
	if (cmd == 'w')
	{
		if (this->map[this->playerPos.y - 1][this->playerPos.x] == 0)
			this->playerPos.y -= 1;
	}
	else if (cmd == 's')
	{
		if (this->map[this->playerPos.y + 1][this->playerPos.x] == 0)
			this->playerPos.y += 1;
	}
	else if (cmd == 'a')
	{
		if (this->map[this->playerPos.y][this->playerPos.x - 1] == 0)
			this->playerPos.x -= 1;
	}
	else if (cmd == 'd')
	{
		if (this->map[this->playerPos.y][this->playerPos.x + 1] == 0)
			this->playerPos.x += 1;
	}
	else if (cmd == 'g' && playerPos.x == portalPos.x && playerPos.y == portalPos.y)
	{
		RandomMap rm(this->MAP_WIDTH, this->MAP_HEIGHT);
		rm.generateMap();
		this->map = rm.getMap();
		this->generatePos();
	}
	else if (cmd == 'a' && target != -1)
	{
		// Wywolanie fight
	}
}

void Map::generatePos()
// TODO: Wylosowane wczesniej pozycje powinny zostac wykluczone z dostepnych pol
{
	// Zmienne przechowujace wylosowana pozycje gracza, przeciwnikow oraz portalu
	int x, y;

	// Wylosowanie pozycji playera
	do
	{
		x = rand() % this->MAP_WIDTH;
		y = rand() % this->MAP_HEIGHT;
	} while (this->map[y][x] != 0);

	this->playerPos = { x, y };

	// Wylosowanie pozycji portalu
	do
	{
		x = rand() % this->MAP_WIDTH;
		y = rand() % this->MAP_HEIGHT;
	} while (this->map[y][x] != 0);

	this->portalPos = { x, y };

	// Generowanie przeciwnikow
	int type;

	// Flaga uzywana do sprawdzania, czy na danej pozycji znajduje sie juz przeciwnik
	bool empty_space;

	while (this->enemies.size() < 10)
	{
		empty_space = true;
		x = rand() % this->MAP_WIDTH;
		y = rand() % this->MAP_HEIGHT;
		type = rand() % 3 + 1;

		if (this->map[y][x] == 0)
		{
			for (int i = 0; i < this->enemies.size(); i++)
			{
				if (this->enemies[i][0] == x && this->enemies[i][1] == y)
				{
					// Jesli na danej pozycji jest juz przeciwnik, flaga przyjmie wartosc false
					empty_space = false;
					break;
				}
			}

			if (empty_space)
				this->enemies.push_back({ x, y, type });
		}
	}
}

Map::~Map()
{
}
