#include "Map.h"
#include <iostream>

using namespace std;
Map::Map()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	fillTable();
}


Map::~Map()
{
}

void Map::show()
{

	for (int y = 0;y < CORD_Y; y++)
	{
		for (int x = 0; x < CORD_X; x++)
		{
			cout << tab[y][x];
		}
		cout << endl;
	}
}

void Map::fillTable()
{

	for (int y = 0; y < CORD_Y; y++)
	{
		for (int x = 0; x < CORD_X; x++)
		{

			if (y == 0 || y == (CORD_Y - 1))
			{
				tab[y][x] = '=';
			}
			else if (y == startY && x == startX) {
				tab[y][x] = '@';
			}
			else if ( x == (CORD_X-1) ||  x == 0  )
			{
				tab[y][x] = '|';
			}
			else
			{
				tab[y][x] = '.';
			}
		}

	}
}
bool Map::ifEmptySpace(int y, int x)
{
	if (tab[y][x] == '.') {
		return true;
	}
	return false;
}

void Map::playerMoveRight(int y, int x)
{
	int temp = x - 1;

	curPosition.X = temp;
	curPosition.Y = y;


	tab[y][temp] = '.';
	SetConsoleCursorPosition(hConsole, curPosition);

	cout << tab[y][temp];

	curPosition.X = x;
	curPosition.Y = y;

	tab[y][x] = '@';
	_sleep(150);
	SetConsoleCursorPosition(hConsole, curPosition);
	cout << tab[y][x];

}

void Map::playerMoveLeft(int y, int x)
{
	int temp = x + 1;

	curPosition.X = temp;
	curPosition.Y = y;


	tab[y][temp] = '.';
	SetConsoleCursorPosition(hConsole, curPosition);

	cout << tab[y][temp];

	curPosition.X = x;
	curPosition.Y = y;

	tab[y][x] = '@';
	_sleep(150);
	SetConsoleCursorPosition(hConsole, curPosition);
	cout << tab[y][x];
}
void Map::playerMoveUp(int y, int x)
{
	int temp = y + 1;

	curPosition.X = x;
	curPosition.Y = temp;


	tab[temp][x] = '.';
	SetConsoleCursorPosition(hConsole, curPosition);

	cout << tab[y][temp];

	curPosition.X = x;
	curPosition.Y = y;

	tab[y][x] = '@';
	_sleep(150);
	SetConsoleCursorPosition(hConsole, curPosition);
	cout << tab[y][x];
}
void Map::playerMoveDown(int y, int x)
{
	int temp = y - 1;

	curPosition.X = x;
	curPosition.Y = temp;


	tab[temp][x] = '.';
	SetConsoleCursorPosition(hConsole, curPosition);

	cout << tab[y][temp];

	curPosition.X = x;
	curPosition.Y = y;

	tab[y][x] = '@';
	_sleep(150);
	SetConsoleCursorPosition(hConsole, curPosition);
	cout << tab[y][x];
}

int Map::getMapX()
{
	return CORD_X-2;
}
int Map::getMapY()
{
	return CORD_Y-2;
}

