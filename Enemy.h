#pragma once
#include <string>
#include <cstdlib>
#include <time.h>
#include <random>
class Enemy
{
protected:
	int creatureHp,creatureDefence,creatureStrength;
	std::string creatureName;
	int creatureTurnAttackValue,creatureLifeSteal,creatureLifeStealRate,creatureStunRate, creatureDodgeRate ; 
public:
	virtual  void creatureHpDecrease(int);
	virtual  bool creatureDodge()const;
	virtual  int creatureAttack();
	virtual bool creatureTryToStealLife();
	virtual void creatureStealLife(int);
	virtual bool creatureTryStun();

	virtual int getCreatureStunRate()const;
	virtual int getCreatureLifeStealRate()const;
	virtual int getCreatureDodgeRate() const;
	virtual int getCreatureStrength() const;
	virtual int getCreatureDefence() const;
	virtual  int getCreatureHp() const;
	virtual std::string getCreatureName()const;
	virtual int getCreatureTurnAttackValue()const;
public:
	Enemy();
};
