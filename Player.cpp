#include "Player.h"
Player::Player()
{
	this->eq = new Equipment();
	playerBaseHp = 140;
	playerBaseStrength = 14;
	playerBaseDefence = 2;
	playerBaseEnergy = 100;
	playerBaseDodgeRate = 5;
	refreshPlayer();
}
void Player::refreshPlayer()
{
	playerDefence = playerBaseDefence + eq->getDefense();
	playerDodgeRate = playerBaseDodgeRate + eq->getDodgeRate();
	playerStrength = playerBaseStrength + eq->getAttack();
	playerHp = playerBaseHp + eq->getHp();
	playerEnergy = playerBaseEnergy + eq->getEnergy();
}

int Player::getPlayerHP()
{
	return playerHp;
}

void Player::playerDecreaseHP(int damageTaken)
{
	if (damageTaken > playerDefence)
		playerHp = playerHp - damageTaken;
}

int Player::playerAttack()
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomAttack(playerStrength-6, playerStrength+3);
	playerTurnAttackValue = randomAttack(randomThings);
	return playerTurnAttackValue;
}

int Player::playerCrushingAttack()
{
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> randomAttack(playerStrength+3,playerStrength+11);
	playerTurnAttackValue = randomAttack(randomThings);
	return playerTurnAttackValue;
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
	std::mt19937 randomThings;
	randomThings.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dodge(0, 100);
	int temp = dodge(randomThings);
	if (temp <= playerDodgeRate)
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
	return playerDodgeRate;
}

int Player::getPlayerStrength() const
{
	return playerStrength;
}


