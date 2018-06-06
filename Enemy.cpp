#include "Enemy.h"

void Enemy::creatureHpDecrease(int damageDone)
{
	if(damageDone>creatureDefence)
		creatureHp = creatureHp - damageDone ;
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
	 std::mt19937 randomThings;
	 randomThings.seed(std::random_device()());
	 std::uniform_int_distribution<std::mt19937::result_type> dodge(0,100);
	 int temp = dodge(randomThings);
		 if (temp <= creatureDodgeRate)
			 return true;
	 return false;
}

int Enemy::creatureAttack()
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomAttack(creatureStrength-6, creatureStrength+2);
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
bool Enemy::creatureTryToStealLife() //funckja przywracajaca zdrowie wampirowi (równość ataku vampira)
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> life(0, 100);
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

bool Enemy::creatureTryStun()  // zwraca prawde jesli jest mana  // zwraca falsz jesli nie ma many lub nie wylosowalo sie
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> stun(0, 100);
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

