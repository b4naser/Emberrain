#include "Enemy.h"
#ifndef VAMPIRE_H
#define VAMPIRE_H
class Vampire :
	public Enemy
{
public:
	Vampire(int, int, int);
	~Vampire();
};
#endif