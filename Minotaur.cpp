#include "Minotaur.h"



Minotaur::Minotaur(int atakPlayera, int obronaPlayera,int hpPlayera)
{
	creatureName = "Minotaur";
	creatureHp = creatureHp = std::rand() % hpPlayera / 2 + hpPlayera / 2 + 10;
	creatureLifeSteal = 0;
	creatureDodgeRate = 5; //dodge
	creatureStrengh = 16; //sila uderzenia
	creatureDefence = 4; //obrona
	creatureStunRate = 5;  //szansa na stuna
}

Minotaur::~Minotaur()
{
}
