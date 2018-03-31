#include <string>
#include <cstdlib>

#ifndef ENEMY_H
#define ENEMY_H
class Enemy
{
protected:
	int creatureHp,creatureDefence,creatureStrengh, creatureDodgeRate;
	std::string creatureName;
	int creatureTurnAttackValue,LifeSteal,minotaurStunRate;;   //potrzebna zmiena do zwracania losowanego ataku 
public:
	virtual  void creatureHpDicrease(int);

	virtual  bool creatureDodge()const;
	virtual  int creatureAttack();
	virtual std::string getCreatureName()const;

	virtual int getCreatureTurnAttackValue()const;
	virtual int getCreatureDefence() const;
	virtual  int getCreatureHp() const;
	virtual int getCreatureStrengh() const;
	virtual int getCreatureDodgeRate() const;
	virtual bool vampireBite();
	virtual void lifeStealing(int);
	virtual int creatureLifeStealRate();
	virtual int getMinotaurStunRate();
	virtual bool minotaurStun();
public:
	Enemy();
};
#endif
