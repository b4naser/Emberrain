#include <Windows.h>
#include "Player.h"
class Map
{
private:
	CONST int startX = 30;
	CONST int startY = 30;

	static CONST int CORD_X = 150;
	static CONST int CORD_Y = 40;
	char tab[CORD_Y][CORD_X];

	HANDLE hConsole;
	COORD curPosition;

public:
	
	Map();
	~Map();
	void show();
	void fillTable();
	bool ifEmptySpace(int y,int x);
	Player player = Player();


	void playerMoveRight(int y,int x);
	void playerMoveLeft(int y, int x);
	void playerMoveDown(int y, int x);
	void playerMoveUp(int y, int x);

	int getMapX();
	int getMapY();

};

