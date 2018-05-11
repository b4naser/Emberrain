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
	const int MAP_WIDTH = 40;
	const int MAP_HEIGHT = 25;
	std::vector< std::vector<int> > map;
	std::vector< std::vector<int> > enemies;
	Pos playerPos;
	Pos portalPos;
	int target;
	Stage *fight = nullptr;
	void generatePos();
public:
	Map();
	virtual void show();
	virtual void command(char cmd);
	~Map();
};

