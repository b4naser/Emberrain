#include "Vampire.h"



Vampire::Vampire()
{
	creatureHp = 120;
	creatureDodgeRate = 5; //dodge
	creatureStrengh = 12; //sila uderzenia
	creatureDefence = 2; //obrona
	LifeSteal = 5;  // wampiryzm
}

bool Vampire::CallOfBlood() //funckja przywracajaca zdrowie wampirowi (równość ataku vampira)
{
	if ((std::rand() % 100) <= LifeSteal) return true;
	else				     return false;
}


Vampire::~Vampire()
{
}
