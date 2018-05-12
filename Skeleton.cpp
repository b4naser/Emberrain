#include "Skeleton.h"
Skeleton::Skeleton(int atakPlayera, int obronaPlayera, int hpPlayera)
{
	creatureName = "Szkielet";
	creatureHp = std::rand() % hpPlayera /2 + hpPlayera / 2 ;
	creatureStunRate = 0;
	creatureLifeSteal = 0;
	creatureDodgeRate = 20; //szansa na dodge 
	creatureStrengh = std::rand() % (atakPlayera-7) + 3;
	creatureDefence = 2;
}

Skeleton::~Skeleton()
{
}

