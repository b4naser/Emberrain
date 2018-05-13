#include "Player.h"
#
Player::Player()
{
	playerHp = 140;
	playerStrength = 14;
	playerDefence = 2;
	playerEnergy = 100;
	playerDodgdeRate = 5;
}

int Player::getPlayerHP()
{
	return playerHp;
}

void Player::playerDecreaseHP(int damageTaken)
{
	if (damageTaken < playerDefence)
		playerHp = playerHp;
	else
		playerHp = playerHp - (damageTaken - playerDefence);
}

int Player::playerAttack()
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomAttack(playerStrength / 2, playerStrength);
	playerTurnAttackValue = randomAttack(randomThings);
	return randomAttack(randomThings);
}

int Player::playerCrushingAttack()
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomAttack(playerStrength,playerStrength+5);
	playerTurnAttackValue = randomAttack(randomThings);
	return randomAttack(randomThings);
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
	int temp = std::rand() % 100;
	if (temp <= playerDodgdeRate)
		return true;
	return false;
}

void Player::playerDecreaseEnergy(int energyDecrease)
{
	playerEnergy -= energyDecrease;
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

Player::~Player()
{
}

int Player::getPlayerTurnAttackValue() const
{
	return playerTurnAttackValue;
}

int Player::getPlayerDodgeRate() const
{
	return playerDodgdeRate;
}

int Player::getPlayerStrength() const
{
	return playerStrength;
}


