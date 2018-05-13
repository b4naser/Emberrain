#pragma once
#include "Item.h"

class Shield 
	:public Item
{
	int DefenseValue;
	int AddEnergyValue;
public:
	Shield();
	int getDefenseValue() const;
	int getAddEnergyValue() const;
	virtual void upgrade();
};
