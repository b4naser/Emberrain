#include "Enemy.h"

void Enemy::creatureHpDecrease(int damageTaken)
{
	if (damageTaken>0)
		creatureHp = creatureHp - damageTaken ;
}

int Enemy::getCreatureHp() const 
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
 bool Enemy::creatureDodge() const
 {
	 std::random_device dev;
	 std::mt19937 randomThings(dev());
	 std::uniform_int_distribution<int> dodge(0,100);
	 int temp = dodge(randomThings);
		 if (temp <= creatureDodgeRate)
			 return true;
	 return false;
}
int Enemy::creatureAttack()
{
	std::random_device dev;
	std::mt19937 randomThings(dev());
	std::uniform_int_distribution<int> randomAttack(creatureStrength-6, creatureStrength+2);
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
bool Enemy::creatureTryToStealLife() 
{
	std::random_device dev;
	std::mt19937 randomThings(dev());
	std::uniform_int_distribution<int> life(0, 100);
	int temp = life(randomThings);
	if (temp <= creatureLifeSteal)
		return true;
	return false;
}

void Enemy::creatureStealLife(int def)
{
	if (creatureHp != 120) {
		creatureHp += (getCreatureTurnAttackValue()-def);
		if (creatureHp > 120) creatureHp = 120;
	}
}

bool Enemy::creatureTryStun()  
{
	std::random_device dev;
	std::mt19937 randomThings(dev());
	std::uniform_int_distribution<int>stun(0, 100);
	int temp = stun(randomThings);
	if (temp <= creatureLifeSteal)
		return true;
	return false;
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

