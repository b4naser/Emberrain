#include "Shield.h"

Shield::Shield() :DefenseValue(2),AddEnergyValue(5)
{
}
int Shield::getDefenseValue() const
{
	return DefenseValue;
}
int Shield::getAddEnergyValue() const 
{
	return AddEnergyValue;
}
void Shield::upgrade()
{
	Level++;
	DefenseValue += 3;
	AddEnergyValue += 3;
}