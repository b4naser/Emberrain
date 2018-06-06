#include "Minotaur.h"



Minotaur::Minotaur(int aPlayer, int dPlayer, int hpPlayer)
{

	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomHP(hpPlayer -20, hpPlayer + 20);
	std::uniform_int_distribution<std::mt19937::result_type> randomDefence(dPlayer-2, dPlayer);
	std::uniform_int_distribution<std::mt19937::result_type> randomStrength(aPlayer -4, aPlayer + 3);
	
	creatureName = "Minotaur";
	creatureHp = randomHP(randomThings);
	creatureLifeSteal = 0;
	creatureDodgeRate = 5; //dodge
	creatureStrength = randomStrength(randomThings);
	creatureDefence = randomDefence(randomThings);

	if(aPlayer>25)
		creatureStunRate = 12;  //szansa na stuna
	else
		creatureStunRate = 5;  //szansa na stuna
}

Minotaur::~Minotaur()
{
}
