#pragma once
#include "Enemy.h"
class Vampire :
	public Enemy
{
private:
	int LifeSteal;
public:
	Vampire();
	bool CallOfBlood();
	~Vampire();
};

