#include "RandomMap.h"
#include <iostream>
#include <random>
#include <time.h>
#include <vector>

/*
	TODO: tempMap mo�na stworzy� jak� zmienna lokalna funkcji kt�re jej potrzebuj�, a nie jako zmienn� klasy
*/

RandomMap::RandomMap(int width, int height) : MAP_WIDTH(width), MAP_HEIGHT(height)
{
	srand(time(NULL));

	// Powi�ksza wektory
	this->map.resize(this->MAP_HEIGHT, std::vector<int>(this->MAP_WIDTH, 0));
	this->tempMap.resize(this->MAP_HEIGHT, std::vector<int>(this->MAP_WIDTH, 0));
}

void RandomMap::randomizeMap()
/*
	Wype�nia tablic� warto�ci� 1 na podstawie prawdopodobie�stwa LIVE_CELL_CHANCE, pozosta�e maj� warto�� 0
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
	Zwraca ilo�� kom�rek danego typu wok� podanego punktu
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
	Krok automatu kom�rkowego. Je�li wok� �ywej kom�rki jest za ma�o �ywych - umiera. Je�li wok� martwej kom�rki jest wystarczaj�co �ywych - staje si� �yw�
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
	Generuje map� korzystaj�c ze definiowanych w klasie metod
*/
{
	this->randomizeMap();
	// Dodaje obramowanie wokol mapy zeby mapa byla zamknieta ...
	this->addCellRect(1, 0, 0, this->MAP_WIDTH, this->MAP_HEIGHT);
	// ... i estetycznie wygl�dala
	this->addCellRect(1, 1, 1, this->MAP_WIDTH-1, this->MAP_HEIGHT-1);
	this->addCellRect(1, 2, 2, this->MAP_WIDTH-2, this->MAP_HEIGHT-2);
	// Dodaje zywe komorki blisko krawedzi mapy co ma zapobiegac tworzeniu sie odizolowanych pomieszczen
	this->addCellRect(0, this->MAP_WIDTH * 1 / 6, this->MAP_HEIGHT * 1 / 6, this->MAP_WIDTH * 5 / 6, this->MAP_HEIGHT * 5 / 6);

	for (int i = 0; i < this->STEPS; i++)
	{
		this->doStep();
		this->map = this->tempMap;
	}

	this->addWallLayers();
}

std::vector< std::vector<int> > RandomMap::getMap()
/*
	Zwraca tablic� z gotow� map�
	TODO: Wypada�oby sprawdzi� czy mapa zosta�a wygenerowana
*/
{
	return this->map;
}