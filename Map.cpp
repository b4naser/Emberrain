#include <iostream>
#include <Windows.h>
#include <vector>
#include "Map.h"

#include <typeinfo>

using namespace std;

Map::Map(int width, int height) : MAP_WIDTH(width), MAP_HEIGHT(height)
{
	// Powiêksza wektor mapy
	this->map.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));
	
	// Tworzy nowego Surface'a
	surface = new Surface(this->MAP_WIDTH, this->MAP_HEIGHT);

	// Generowanie map
	RandomMap rm(70, 40);
	rm.generateMap();

	this->map = rm.getMapArray();

	this->playerPosition.x = 5;
	this->playerPosition.y = 5;
}

void Map::show()
{
	/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < this->MAP_HEIGHT; i++)
	{
		for (int j = 0; j < this->MAP_WIDTH; j++)
		{
			if (i == playerPosition.y && j == playerPosition.x)
			{
				SetConsoleTextAttribute(hConsole, 111);
				cout << "@";
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
		}
		cout << endl;
	}

	SetConsoleTextAttribute(hConsole, 15);*/
}

void Map::command(char cmd)
{
	switch (cmd)
	{
	case 'w':
		this->playerPosition.y -= 1;
		break;
	case 's':
		this->playerPosition.y += 1;
		break;
	case 'a':
		this->playerPosition.x -= 1;
		break;
	case 'd':
		this->playerPosition.x += 1;
		break;
	default:
		cout << "Czego Ty ode mnie chcesz?";
	}
}

Map::~Map()
{
}
