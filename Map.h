#pragma once
#include <vector>
#include "Stage.h"
#include "RandomMap.h"
#include "Player.h"

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
	Player* player;
	Pos playerPos;
	Pos portalPos;
	int target;
	void generatePos();
	bool defeated = false;
	int level;
public:
	Map(Player *p);
	virtual void show();
	virtual void command(char cmd);
	bool isDefeated() const;
	~Map();
};

