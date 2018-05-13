#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon():AttackValue(5)
{
}
int Weapon::getAttackValue() const
{
	return AttackValue;
}

void Weapon::upgrade()
{
	Level++;
	AttackValue += 3;
}