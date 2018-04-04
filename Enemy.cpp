#include "Enemy.h"

void Enemy::creatureHpDicrease(int damageDone)
{
	creatureHp = creatureHp - (damageDone-creatureDefence);
}

int Enemy::getCreatureHp() const 
{
	return creatureHp;
}

int Enemy::getCreatureStrengh() const
{
	return creatureStrengh;
}

int Enemy::getCreatureDodgeRate() const
{
	return creatureDodgeRate;
}





 bool Enemy::creatureDodge() const //zwraca ilosc uniku
{
	 int temp = (std::rand() % 100);
		 if (temp <= creatureDodgeRate)
			 return true;
	 return false;
}

int Enemy::creatureAttack()
{
	int attack = ( (std::rand() % ((creatureStrengh/2)+1) ) + (creatureStrengh / 2) );
	creatureTurnAttackValue = attack;
	return attack;
}

std::string Enemy::getCreatureName() const
{
	return creatureName;
}

int Enemy::getCreatureTurnAttackValue() const
{
	return creatureTurnAttackValue;
}

int Enemy::getCreatureDefence() const
{
	return creatureDefence;
}
bool Enemy::vampireBite() 
{
	if ((std::rand() % 100) <= LifeSteal) return true;
	else						        	return false;
	return false;
}

void Enemy::lifeStealing(int def)
{
	if (creatureHp != 120) {
		creatureHp += (getCreatureTurnAttackValue()-def);
		if (creatureHp > 120) creatureHp = 120;
	}
		

}

int Enemy::creatureLifeStealRate()
{
	return LifeSteal;
}
bool Enemy::minotaurStun()  
{
	if ((std::rand() % 100) <= minotaurStunRate) return true;
	else										 return false;
}

Enemy::Enemy()
{
}



int Enemy::getMinotaurStunRate()
{
	return minotaurStunRate;
}

