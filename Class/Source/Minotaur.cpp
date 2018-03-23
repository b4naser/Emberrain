#include "Minotaur.h"



Minotaur::Minotaur()
{
	creatureHp = 140;
	creatureDodgeRate = 5; //dodge
	creatureStrengh = 16; //sila uderzenia
	creatureDefence = 4; //obrona
	stun = 5;  //szansa na stuna
}

bool Minotaur::minotaurStun() 
{
		if ((std::rand() % 100) <= stun) return true;
		else							return false;
}

Minotaur::~Minotaur()
{
}


