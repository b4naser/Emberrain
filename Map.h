#pragma once
#include <vector>
#include "Stage.h"
#include "RandomMap.h"
#include "Surface.h"

typedef struct Pos {
	int x;
	int y;
} Pos;

class Map : public Stage
{
private:
	const int MAP_WIDTH;
	const int MAP_HEIGHT;
	std::vector< std::vector<int> > map;
	std::vector< std::vector<int> > enemies;
	Surface* surface;
	Pos playerPosition = {10, 10};
public:
	Map(int width, int height);
	virtual Surface* getSurface();
	virtual void command(char cmd);
	~Map();
};

