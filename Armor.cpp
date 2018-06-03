#include "Armor.h"

Armor::Armor() : DefenseValue(2),AddHpValue(10)
{
}

int Armor::getDefenseValue() const
{
	return DefenseValue;
}

int Armor::getAddHpValue() const
{
	return AddHpValue;
}

void Armor::upgrade()
{	
	Level++;
	DefenseValue += 2;
	AddHpValue += 10;
	
}