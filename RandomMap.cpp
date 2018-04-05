#include "RandomMap.h"
#include <iostream>
#include <random>
#include <time.h>
#include <vector>

using namespace std;

/*
	TODO: tempMap mo¿na stworzyæ jak¹ zmienna lokalna funkcji które jej potrzebuj¹, a nie jako zmienn¹ klasy
*/

RandomMap::RandomMap(int width, int height) : MAP_WIDTH(width), MAP_HEIGHT(height)
{
	srand(time(NULL));

	// Powiêksza wektory
	this->map.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));
	this->tempMap.resize(this->MAP_HEIGHT, vector<int>(this->MAP_WIDTH, 0));
}

void RandomMap::randomizeMap()
/*
	Wype³nia tablicê wartoœci¹ 1 na podstawie prawdopodobieñstwa LIVE_CELL_CHANCE, pozosta³e maj¹ wartoœæ 0
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

void RandomMap::addCellRect(int cellType, int xx, int yy, int width, int height)
/*
	Dodaje w wyznaczona pozycje prostokat o danym typie o podanych wymiarach
*/
{
	for (int y = yy; y < height; y++)
	{
		for (int x = xx; x < width; x++)
		{
			if ((y == yy) || (y == height - 1) || (x == xx) || (x == width - 1))
				map[y][x] = cellType;
		}
	}
}

int RandomMap::getNeightboursCount(int cellType, int x, int y, bool countOutbounds = false)
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
			else if (map[i][j] == cellType)
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

void RandomMap::addWallLayers()
{
	// Dodaje 1 warstwe skal
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
	this->map = this->tempMap;

	// Dodaje 2 warstwe skal
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
	this->map = this->tempMap;

	// Dodaje 3 warstwe skal
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
	this->map = this->tempMap;
}

void RandomMap::generateMap()
/*
	Generuje mapê korzystaj¹c ze definiowanych w klasie metod
*/
{
	this->randomizeMap();
	// Dodaje obramowanie wokol mapy zeby mapa byla zamknieta
	this->addCellRect(1, 0, 0, this->MAP_WIDTH, this->MAP_HEIGHT);
	// Dodaje zywe komorki blisko krawedzi mapy co ma zapobiegac tworzeniu sie odizolowanych pomieszczen
	this->addCellRect(0, this->MAP_WIDTH * 1 / 9, this->MAP_HEIGHT * 1 / 9, this->MAP_WIDTH * 8 / 9, this->MAP_HEIGHT * 8 / 9);
	for (int i = 0; i < this->STEPS; i++)
	{
		this->doStep();
		this->map = this->tempMap;
	}
	this->addWallLayers();
}

vector< vector<int> > RandomMap::getMap()
/*
	Zwraca tablicê z gotow¹ map¹
	TODO: Wypada³oby sprawdziæ czy mapa zosta³a wygenerowana
*/
{
	return this->map;
}

std::vector<std::vector<int>> RandomMap::getEnemies()
{
	std::vector< std::vector<int> > enemies;

	int x, y, type;

	while (enemies.size() < 10)
	{
		x = rand() % this->MAP_WIDTH;
		y = rand() % this->MAP_HEIGHT;
		type = rand() % 3 + 1;
	// TODO: Sprawdzac czy na danej pozycji juz nie ma przeciwnikow
		if (this->map[y][x] == 0)
		{
			enemies.push_back({ x, y, type });
		}

	}

	return enemies;
}