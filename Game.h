#pragma once
#include <Windows.h>
#include "Stage.h"
class Game
{
private:
	bool running;
	HANDLE hConsole;
	Stage *stage;
public:
	Game();
	void run();
	~Game();
};

