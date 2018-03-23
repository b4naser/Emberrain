#pragma once
#include "Enemy.h"
class Minotaur :
	public Enemy
{
private:
	int stun;
public:
	Minotaur();
	bool minotaurStun();
	~Minotaur();
};

