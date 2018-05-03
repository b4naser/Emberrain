#include <string>
#include <cstdlib>

#ifndef ENEMY_H
#define ENEMY_H
class Enemy
{
protected:
	int creatureHp,creatureDefence,creatureStrengh;
	std::string creatureName;
	int creatureTurnAttackValue,creatureLifeSteal,creatureLifeStealRate,creatureStunRate, creatureDodgeRate ;   //potrzebna zmiena do zwracania losowanego ataku 
public:
	virtual  void creatureHpDicrease(int);
	virtual  bool creatureDodge()const;
	virtual  int creatureAttack();
	virtual bool creatureReturningLife();
	virtual void creatureTryLifeStealing(int);
	virtual bool creatureTryStun();

	virtual int getCreatureStunRate()const;
	virtual int getCreatureLifeStealingRate()const;
	virtual int getCreatureDodgeRate() const;
	virtual int getCreatureStrengh() const;
	virtual int getCreatureDefence() const;
	virtual  int getCreatureHp() const;
	virtual std::string getCreatureName()const;
	virtual int getCreatureTurnAttackValue()const;
public:
	Enemy();
};
#endif
