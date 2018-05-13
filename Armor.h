#pragma once
#include "Item.h"

class Armor : public Item
{
	int DefenseValue;
	int AddHpValue;
public:
	Armor();
	int getDefenseValue() const;
	int getAddHpValue() const;
	virtual void upgrade();
};
