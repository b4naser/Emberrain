#include <iostream>
#include <Windows.h>
#include <vector>
#include "Map.h"

#include <typeinfo>

using namespace std;

Map::Map()
{
	// Powiêksza wektor
	this->map.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));

	// Generowanie map
	RandomMap rm;

	rm.generateMap();

	this->map = rm.getMapArray();

	this->playerPosition.x = 5;
	this->playerPosition.y = 5;
}

void Map::show()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < this->MAP_HEIGHT; i++)
	{
		for (int j = 0; j < this->MAP_WIDTH; j++)
		{
			if (i == 30 && j == 30)
			{
				SetConsoleTextAttribute(hConsole, 44);
				cout << char(206);
				continue;
			}

			if (this->map[i][j] == 0)
			{
				SetConsoleTextAttribute(hConsole, 98);
				cout << char(178);
			}
			else if (this->map[i][j] == 1)
			{
				SetConsoleTextAttribute(hConsole, 136);
				cout << char(219);
			}
			else if (this->map[i][j] == 2)
			{
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(176);
			}
			else if (this->map[i][j] == 3)
			{
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(177);
			}
			else if (this->map[i][j] == 4)
			{
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(178);
			}
			/*
						if (this->map[i][j] == 0)
			{
				SetConsoleTextAttribute(hConsole, 34);
				cout << char(219);
			}
			else if (this->map[i][j] == 1)
			{
				SetConsoleTextAttribute(hConsole, 136);
				cout << char(219);
			}
			else if (this->map[i][j] == 2)
			{
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(176);
			}
			else if (this->map[i][j] == 3)
			{
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(177);
			}
			else if (this->map[i][j] == 4)
			{
				SetConsoleTextAttribute(hConsole, 120);
				cout << char(178);
			}*/
		}
		cout << endl;
	}

	SetConsoleTextAttribute(hConsole, 15);
}

void Map::command(char cmd)
{
	switch (cmd)
	{
	case 'w':
		cout << "Idem w gore";
		break;
	case 's':
		cout << "Idem w dul";
		break;
	case 'a':
		cout << "Idem w lewo";
		break;
	case 'd':
		cout << "Idem w prawo";
		break;
	default:
		cout << "Czego Ty ode mnie chcesz?";
	}
}

Map::~Map()
{
}
