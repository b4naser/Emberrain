#pragma once
#include "Item.h"

class Weapon : public Item
{
	int AttackValue;

public:
	Weapon();
	int getAttackValue() const;
	virtual void upgrade();
};