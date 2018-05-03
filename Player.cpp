#include "Player.h"
#
Player::Player()
{
	playerHp = 140;
	playerStrengh = 14;
	playerDefence = 2;
	playerEnergy = 100;
	playerDodgdeRate = 5;
}

int Player::getPlayerHP()
{
	return playerHp;
}

void Player::playerDicreaseHP(int damageTaken)
{
	playerHp = playerHp - (damageTaken - playerDefence);
}

void Player::playerIncreaseHP()
{
	if (playerEnergy >= 30) {
		playerEnergy -= 20; 
		playerHp += ( (std::rand() % 15) + playerDefence );
	}
}

int Player::playerAttack()
{
	int attack = (std::rand() % (playerStrengh - (playerStrengh/2) ) + playerStrengh/2);
	playerTurnAttackValue = attack;
	return attack;
}

int Player::playerCrushingAttack()
{
		int specialAttack = ((std::rand() % (playerStrengh)) + 12);
		playerTurnAttackValue = specialAttack;
		return specialAttack;
	
}

int Player::getPlayerEnergy()
{
	return playerEnergy;
}

void Player::playerIncreaseEnergy()
{
	if (playerEnergy < 100) {
		playerEnergy += 5;
		if(playerEnergy > 100) {
			playerEnergy = 100;
		}
	}
	
}

bool Player::playerDodging()
{
	int temp = (std::rand() % 100);
	if (temp <= playerDodgdeRate)
		return true;
	return false;
}

void Player::playerDicreaseEnergy(int x)
{
	playerEnergy -= x;
}

std::string Player::getPlayerName()
{
	return playerName;
}

int Player::getPlayerDefence()
{
	return playerDefence;
}

void Player::setPlayerName(std::string name)
{
	playerName = name;
}

int Player::getPlayerTurnAttackValue() const
{
	return playerTurnAttackValue;
}

int Player::getPlayerDodgeRate() const
{
	return playerDodgdeRate;
}

int Player::getPlayerStrengh() const
{
	return playerStrengh;
}


Player::~Player()
{
}

