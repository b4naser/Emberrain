#pragma once
#include <vector>
#include "Stage.h"
#include "RandomMap.h"

typedef struct Pos {
	int x;
	int y;
} Pos;

class Map : public Stage
{
private:
	const int MAP_WIDTH = 70;
	const int MAP_HEIGHT = 40;
	std::vector< std::vector<int> > map;
	Pos playerPosition;
public:
	Map();
	virtual void show();
	virtual void command(char cmd);
	~Map();
};

