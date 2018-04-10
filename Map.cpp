#include <iostream>
#include <Windows.h>
#include <vector>
#include "Map.h"

#include <typeinfo>

using namespace std;

COORD mapPosition{ 0, 0 };
COORD mapPrintSize{ 7, 5 }; // Niezale¿nie od podania liczby parzystej czy nieparzystej znak gracza zawsze bêdzie na œrodku. W przypadku podania parzystej rozmiar zostanie zwiêkszony o 1

Map::Map(int width, int height) : MAP_WIDTH(width), MAP_HEIGHT(height)
{
	// Powiêksza wektor mapy
	this->map.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));

	// Tworzy nowego Surface'a
	surface = new Surface(30, 30);

	// Generowanie mapy
	RandomMap rm(30, 30);
	rm.generateMap();

	// Przepisanie randomowej mapy
	this->map = rm.getMap();

	// Przepisanie wspolrzednych przeciwnikow
	this->enemies = rm.getEnemies();
}

Surface* Map::getSurface()
{
	vector< string > actions;

	// i, j wykorzystywane sa do ustalania pozycji na ktorej ma byc dodany znak do Surface
	int i, j = mapPosition.Y;
	// Iteracja po mapie wzglêdem pozycji playera
	for (int y = this->playerPosition.y - mapPrintSize.Y / 2; y < this->playerPosition.y + mapPrintSize.Y / 2 + 1; y++)
	{
		i = mapPosition.X;
		for (int x = this->playerPosition.x - mapPrintSize.X / 2; x < this->playerPosition.x + mapPrintSize.X / 2 + 1; x++)
		{
			// Dodaje playera na srodek wyswietlanej mapy
			if (j == mapPrintSize.Y / 2 && i == mapPrintSize.X / 2)
			{
				this->surface->printAt("@", 47, j, i);
				goto cntn;
			}

			// Jesli na danej pozycji znajduje sie przeciwnik - dodaje go do Surface'a
			for (int k = 0; k < this->enemies.size(); k++)
			{
				if (this->enemies[k][1] == y && this->enemies[k][0] == x)
				{
					// Dostosowuje kolor na podstawie typu przeciwnika
					switch (this->enemies[k][2])
					{
					case 1:
						this->surface->printAt(char(2), 41, j, i);
						break;
					case 2:
						this->surface->printAt(char(2), 43, j, i);
						break;
					case 3:
						this->surface->printAt(char(2), 46, j, i);
						break;
					}

					goto cntn;
				}
			}

			if (y < 0 || x < 0 || y > this->MAP_HEIGHT - 1 || x > this->MAP_WIDTH - 1)
				// Jeœli iteracja odbywa siê poza granicami wektora mapy to przestrzen ta jest zastepowana szarym blokiem
				this->surface->printAt(char(219), 136, j, i);
			else
			{
				// Obsluga kolorow komorek mapy
				switch (this->map[y][x])
				{
				case 0:
					this->surface->printAt(char(178), 98, j, i);
					break;
				case 1:
					this->surface->printAt(char(219), 136, j, i);
					break;
				case 2:
					this->surface->printAt(char(176), 120, j, i);
					break;
				case 3:
					this->surface->printAt(char(177), 120, j, i);
					break;
				case 4:
					this->surface->printAt(char(178), 120, j, i);
					break;
				}
			}

		cntn:
			i++;
		}
		j++;
	}

	// Sprawdza otoczenie gracza pod katem ewentualnych akcji
	for (int y = this->playerPosition.y - 1; y < this->playerPosition.y + 2; y++)
	{
		for (int x = this->playerPosition.x - 1; x < this->playerPosition.x + 2; x++)
		{
			// Czy jest jakis przeciwnik?
			for (int k = 0; k < this->enemies.size(); k++)
			{
				if (this->enemies[k][1] == y && this->enemies[k][0] == x)
				{
					actions.push_back("z - zaatakuj");
				}
			}
		}
	}

	// Wypisanie wszystkich mozliwych akcji
	for (int i = 0; i < actions.size(); i++)
	{
		this->surface->printAt(actions[i], 67, 1 + i, 5);
	}

	return this->surface;
}

void Map::command(char cmd)
{
	this->surface->clear();

	switch (cmd)
	{
	case 'w':
		if (this->map[this->playerPosition.y - 1][this->playerPosition.x] == 0)
			this->playerPosition.y -= 1;
		break;
	case 's':
		if (this->map[this->playerPosition.y + 1][this->playerPosition.x] == 0)
			this->playerPosition.y += 1;
		break;
	case 'a':
		if (this->map[this->playerPosition.y][this->playerPosition.x - 1] == 0)
			this->playerPosition.x -= 1;
		break;
	case 'd':
		if (this->map[this->playerPosition.y][this->playerPosition.x + 1] == 0)
			this->playerPosition.x += 1;
		break;
	}

}

Map::~Map()
{
}
