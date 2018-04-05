#pragma once
#include <Windows.h>
#include "Stage.h"
#include "Surface.h"
class Game
{
private:
	bool running;
	HANDLE hConsole;
	Surface* gameSurface;
	Stage *stage;
public:
	Game();
	void run();
};

