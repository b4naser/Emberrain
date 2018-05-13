#pragma once
#include "Item.h"

class Boots
	: public Item
{
	int DefenseValue;
	int AddDodgeRateValue;
public:
	Boots();
	int getDefenseValue() const;
	int getAddDodgeRateValue() const;
	virtual void upgrade();
};
