#pragma once
#include "Stage.h"
#include "Shield.h"
#include "Weapon.h"
#include "Armor.h"
#include "Boots.h"

class Equipment : public Stage
{	
private:
	Weapon* weapon;
	Shield* shield;
	Armor* armor;
	Boots* boots;
	int crystals;

public:
	Equipment();
	int getDefense() const;
	int getAttack() const;
	int getDodgeRate() const;
	int getEnergy() const;
	int getHp() const;
	int getCrystals() const;
	void addCrystals(int);
	void subCrystals(int);
	void show();
	void command(char cmd);
	~Equipment();
};



