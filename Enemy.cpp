#include "Enemy.h"

void Enemy::creatureHpDecrease(int damageDone)
{
	if(damageDone>creatureDefence)
		creatureHp = creatureHp - damageDone + creatureDefence;
}

int Enemy::getCreatureHp() const //zwraca hp
{
	return creatureHp;
}
int Enemy::getCreatureStrength() const
{
	return creatureStrength;
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
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomAttack(creatureStrength / 2, creatureStrength);
	creatureTurnAttackValue = randomAttack(randomThings);
	return 	creatureTurnAttackValue;
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
	else						        		  return false;
}

void Enemy::creatureTryLifeSteal(int def)
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

int Enemy::getCreatureLifeStealRate()const
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
