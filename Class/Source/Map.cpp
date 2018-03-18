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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

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
	
	curPosition.X = 130;
	curPosition.Y = 1;
	tab[y][x] = '@';
	SetConsoleCursorPosition(hConsole, curPosition);
	cout << tab[y][x];

}

void Map::playerMoveLeft(int y, int x)
{
	curPosition.X = x;
	curPosition.Y = y;
	int temp = x + 1;
	tab[y][temp] = ' ';
	tab[y][x] = '@';
	SetConsoleCursorPosition(hConsole, curPosition);
}
void Map::playerMoveUp(int y, int x)
{
	curPosition.X = x;
	curPosition.Y = y;
	int temp = y - 1;
	tab[y][temp] = ' ';
	tab[y][x] = '@';
	SetConsoleCursorPosition(hConsole, curPosition);
}
void Map::playerMoveDown(int y, int x)
{
	curPosition.X = x;
	curPosition.Y = y;
	int temp = y + 1;
	tab[y][temp] = ' ';
	tab[y][x] = '@';
	SetConsoleCursorPosition(hConsole, curPosition);
}

int Map::getMapX()
{
	return CORD_X-2;
}
int Map::getMapY()
{
	return CORD_Y-2;
}

