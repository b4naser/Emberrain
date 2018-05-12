#include "Enemy.h"

void Enemy::creatureHpDicrease(int damageDone)
{
	creatureHp = creatureHp - (damageDone-creatureDefence);
}

int Enemy::getCreatureHp() const //zwraca hp
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
 bool Enemy::creatureDodge() const //zwraca ilosc uniku procentowo
{
	 int temp = (std::rand() % 100);
		 if (temp <= creatureDodgeRate)
			 return true;
	 return false;
}

int Enemy::creatureAttack()
{
	int attack = (std::rand() % (creatureStrengh - (creatureStrengh / 2)) + creatureStrengh / 2);
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
bool Enemy::creatureReturningLife() //funckja przywracajaca zdrowie wampirowi (równoœæ ataku vampira)
{
	if ((std::rand() % 100) <= creatureLifeSteal) return true;
	else						        	return false;
	return false;
}

void Enemy::creatureTryLifeStealing(int def)
{
	if (creatureHp != 120) {
		creatureHp += (getCreatureTurnAttackValue()-def);
		if (creatureHp > 120) creatureHp = 120;
	}
		

}

bool Enemy::creatureTryStun()  // zwraca prawde jesli jest mana  // zwraca falsz jesli nie ma many lub nie wylosowalo sie
{
	if ((std::rand() % 100) <= creatureStunRate) return true;
	else										 return false;
}

int Enemy::getCreatureLifeStealingRate()const
{
	return creatureLifeSteal;
}
Enemy::Enemy()
{
}
int Enemy::getCreatureStunRate()const
{
	return creatureStunRate;
}

