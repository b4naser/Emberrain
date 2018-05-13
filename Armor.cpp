#include "Armor.h"
#include "stdafx.h"

Armor::Armor() : DefenseValue(5),AddHpValue(20)
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
	DefenseValue += 3;
	AddHpValue += 20;
	
}