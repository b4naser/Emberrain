#include "Boots.h"
#include "stdafx.h"

Boots::Boots() : DefenseValue(2), AddDodgeRateValue(1)
{
}

int Boots::getDefenseValue() const
{
	return DefenseValue;
}

int Boots::getAddDodgeRateValue() const
{
	return AddDodgeRateValue;
}

void Boots::upgrade()
{
	Level++;
	DefenseValue += 1;
	AddDodgeRateValue += 1;

}