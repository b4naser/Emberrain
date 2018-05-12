#include "Vampire.h"


Vampire::Vampire(int atakPlayera, int obronaPlayera, int hpPlayera)
{
	srand(time(NULL));
	creatureName = "Wampir";
	creatureHp = std::rand() % hpPlayera/2 + hpPlayera/2 - 10;
	creatureStunRate = 0;
	creatureDodgeRate = 5; //dodge
	creatureStrengh = std::rand() % (atakPlayera/2) + (atakPlayera- (atakPlayera / 2));
	creatureDefence = std::rand() % (obronaPlayera - 3) + 3;
	creatureLifeSteal = 35;  // wampiryzm
}



Vampire::~Vampire()
{
}
