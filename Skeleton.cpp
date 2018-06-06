#include "Skeleton.h"
Skeleton::Skeleton(int aPlayer, int dPlayer, int hpPlayer)
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomHP(hpPlayer / 2, hpPlayer-20); 
	std::uniform_int_distribution<std::mt19937::result_type> randomDefence(dPlayer-4, dPlayer-1);
	std::uniform_int_distribution<std::mt19937::result_type> randomStrength(aPlayer -5, aPlayer - 3);

	creatureName = "Szkielet";
	creatureHp = randomHP(randomThings);
	creatureStrength = randomStrength(randomThings);
	creatureStunRate = 0;
	creatureLifeSteal = 0;
	creatureDefence = randomDefence(randomThings);
	creatureDodgeRate = 15;
	if (aPlayer >= 20)
		creatureDodgeRate = 25; //szansa na dodge 
	 else if (aPlayer >= 25)
		creatureDodgeRate =35;

	

}

Skeleton::~Skeleton()
{
}
