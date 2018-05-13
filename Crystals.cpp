#include "Crystals.h"
#include <random>
#include <time.h>

Crystals::Crystals():CrystalsAmount(0)
{
}

int Crystals::earnCrystals()
{
	srand(time(NULL));
	int x = rand() % 31;
	this->amount += x;
	return x;
}
int Crystals::getCrystalsAmount() const
{
	return CrystalsAmount;
}