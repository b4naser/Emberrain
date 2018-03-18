#include <iostream>
#include "Map.h"
using namespace std;


int main() 
{
	Map map = Map();
	int y = 30, x = 30;
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);

	map.show();
	
	while (true) {

		if (GetAsyncKeyState(VK_UP)) {
			if (y > 1 && y <= map.getMapY() ) {
				y--;
				if (map.ifEmptySpace(y,x)) {
					map.playerMoveUp(y, x);
				}
				else y++;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			if (y >= 1 && y <  map.getMapY() ) {
				y++;
				if (map.ifEmptySpace(y, x)) {
					map.playerMoveDown(y, x);
				}
				else y--;
			}

		}
		else if (GetAsyncKeyState(VK_LEFT)) {
			if (x > 1 && x <= map.getMapX() ) {
				x--;
				if (map.ifEmptySpace(y, x)) {
					map.playerMoveLeft(y, x);
				}
				else x++;
			}

		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			if (x >= 1 && x < map.getMapX() ) {
				x++;
				if (map.ifEmptySpace(y, x)) {
					//cout << x<< " " << y;
					map.playerMoveRight(y,x);
				}
				else x--;
			}

		}

	}
	



	getchar();
	getchar();
	return 0;
}
