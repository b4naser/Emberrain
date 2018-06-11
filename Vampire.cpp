#include "Vampire.h"


Vampire::Vampire(int aPlayer, int dPlayer, int hpPlayer)
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomHP(hpPlayer - 25, hpPlayer -10);
	std::uniform_int_distribution<std::mt19937::result_type> randomDefence(dPlayer-2, dPlayer);
	std::uniform_int_distribution<std::mt19937::result_type> randomStrength(aPlayer - 4, aPlayer-1);

	creatureName = "Wampir";
	creatureHp = randomHP(randomThings);
	creatureStunRate = 0;
	creatureDodgeRate = 10; //dodge
	creatureStrength = randomStrength(randomThings);
	creatureDefence = randomDefence(randomThings);
	creatureLifeSteal = 35;  // wampiryzm

	if (aPlayer>25)
		creatureLifeSteal = 45;  
	else if(aPlayer>25 && dPlayer>20)
		creatureLifeSteal = 50;  
}

Vampire::~Vampire()
{
}
