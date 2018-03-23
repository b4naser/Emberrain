#include "Enemy.h"

void Enemy::creatureHpDicrease(int damageDone)
{
	creatureHp -= (damageDone-creatureDefence);
}



int Enemy::getCreatureHp() const //zwraca hp
{
	return creatureHp;
}

 bool Enemy::creatureDodge() const //zwraca ilosc uniku procentowo
{
	 int temp = (std::rand() % 100);
		 if (temp <= creatureDodgeRate)
			 return true;
	 return false;
}

int Enemy::creatureAttack() const
{
	int attack = ( (std::rand() % ((creatureStrengh/2)+1) ) + (creatureStrengh / 2) );
	return attack;
}

