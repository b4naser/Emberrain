#include "RandomMap.h"
#include <iostream>
#include <random>
#include <time.h>
#include <vector>
#include <Windows.h>

using namespace std;

RandomMap::RandomMap()
{
	srand(time(NULL));

	// Powiêksza wektory
	this->map.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));
	this->tempMap.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));
}

void RandomMap::randomizeMap()
/*
	Tworzy ¿ywe komórki na podstawie prawdopodobieñsta LIVE_CELL_CHANCE, pozosta³e staj¹ siê martwe.
*/
{
	for (int y = 0; y < this->MAP_HEIGHT; y++)
	{
		for (int x = 0; x < this->MAP_WIDTH; x++)
		{
			if ((rand() % 100) < (this->LIVE_CELL_CHANCE * 100))
				map[y][x] = 1;
			else
				map[y][x] = 0;
		}
	}
}

void RandomMap::addBorder()
/*
	Dodaje wokó³ ca³ej mapy pojedyñcz¹ warstwê ¿ywych komórek, która zapobiega powstawaniu niedomkniêtych krawêdzi mapy
*/
{
	for (int y = 0; y < this->MAP_HEIGHT; y++)
	{
		for (int x = 0; x < this->MAP_WIDTH; x++)
		{
			if ((y == 0) || (y == MAP_HEIGHT - 1) || (x == 0) || (x == MAP_WIDTH - 1))
				map[y][x] = 1;
		}
	}
}

int RandomMap::getNeightboursCount(int type, int x, int y, bool countOutbounds = false)
/*
	Zwraca iloœæ komórek danego typu wokó³ podanego punktu
*/
{
	int count = 0;
	for (int i = y - 1; i <= y + 1; i++)
	{
		for (int j = x - 1; j <= x + 1; j++)
		{
			if ((j == x) && (i == y))
				continue;

			if (((i < 0) || (i > this->MAP_HEIGHT - 1) || (j < 0) || (j > this->MAP_WIDTH - 1)))
			{
				if (countOutbounds)
					count += 1;
			}
			else if (map[i][j] == type)
				count += 1;

			//if ((i < 0) || (i > this->MAP_HEIGHT - 1) || (j < 0) || (j > this->MAP_WIDTH - 1))
			//	count += 1;
			//else
			//	count += map[i][j];
		}
	}
	return count;
}

void RandomMap::doStep()
/*
	Krok automatu komórkowego. Jeœli wokó³ ¿ywej komórki jest za ma³o ¿ywych - umiera. Jeœli wokó³ martwej komórki jest wystarczaj¹co ¿ywych - staje siê ¿yw¹
*/
{
	for (int y = 0; y < this->MAP_HEIGHT; y++)
	{
		for (int x = 0; x < this->MAP_WIDTH; x++)
		{
			if (this->map[y][x])
			{
				if (this->getNeightboursCount(1, x, y, true) < this->DEAD_LIMIT)
					this->tempMap[y][x] = 0;
				else
					this->tempMap[y][x] = 1;
			}
			else
			{
				if (this->getNeightboursCount(1, x, y, true) > this->LIVE_LIMIT)
					this->tempMap[y][x] = 1;
				else
					this->tempMap[y][x] = 0;
			}
		}
	}
}

void RandomMap::addFirstWallBorder()
{
	for (int y = 0; y < this->MAP_HEIGHT; y++)
	{
		for (int x = 0; x < this->MAP_WIDTH; x++)
		{
			if (this->map[y][x])
			{
				if (this->getNeightboursCount(1, x, y, true) < 8)
					this->tempMap[y][x] = 2;
			}
		}
	}
}

void RandomMap::addSecondWallBorder()
{
	for (int y = 0; y < this->MAP_HEIGHT; y++)
	{
		for (int x = 0; x < this->MAP_WIDTH; x++)
		{
			if (this->map[y][x])
			{
				if (this->getNeightboursCount(2, x, y) > 0 && this->getNeightboursCount(0, x, y) == 0)
					this->tempMap[y][x] = 3;
			}
		}
	}
}

void RandomMap::addThirdWallBorder()
{
	for (int y = 0; y < this->MAP_HEIGHT; y++)
	{
		for (int x = 0; x < this->MAP_WIDTH; x++)
		{
			if (this->map[y][x])
			{
				if (this->getNeightboursCount(3, x, y) > 0 && this->getNeightboursCount(2, x, y) == 0)
					this->tempMap[y][x] = 4;
			}
		}
	}
}

void RandomMap::generateMap()
/*
	Generuje mapê korzystaj¹c ze definiowanych w klasie metod
*/
{
	this->randomizeMap();
	this->addBorder();
	for (int i = 0; i < this->STEPS; i++)
	{
		this->doStep();
		this->map = this->tempMap;
	}
	this->addFirstWallBorder();
	this->map = this->tempMap;
	this->addSecondWallBorder();
	this->map = this->tempMap;
	this->addThirdWallBorder();
	this->map = this->tempMap;
}

void RandomMap::print_map()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < this->MAP_HEIGHT; i++)
	{
		for (int j = 0; j < this->MAP_WIDTH; j++)
		{
			//printf("[%d, %d] = %d\n", j, i, map[i][j]);
			if (this->map[i][j] == 0)
				SetConsoleTextAttribute(hConsole, 68);
			else if (this->map[i][j] == 1)
				SetConsoleTextAttribute(hConsole, 136);

			cout << this->map[i][j];
		}
		cout << endl;
	}

	SetConsoleTextAttribute(hConsole, 7);
}

vector< vector<int> > RandomMap::getMapArray()
/*
	Zwraca tablicê z gotow¹ map¹
	TODO: Wypada³oby sprawdziæ czy mapa zosta³a wygenerowana
*/
{
	return this->map;
}



RandomMap::~RandomMap()
{
}
