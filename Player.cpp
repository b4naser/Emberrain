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
	if(damageTaken>0)
		playerHp = playerHp - damageTaken;
}

int Player::playerAttack()
{
	std::random_device dev;
	std::mt19937 randomThings(dev());
	std::uniform_int_distribution<int> randomAttack(playerStrength-6, playerStrength+3);
	playerTurnAttackValue = randomAttack(randomThings);
	return playerTurnAttackValue;
}

int Player::playerCrushingAttack()
{
	std::random_device dev;
	std::mt19937 randomThings(dev());
	std::uniform_int_distribution<int> randomAttack(playerStrength+8,playerStrength+12);
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
bool Player::playerTryToDodge()
{
	std::random_device dev;
	std::mt19937 randomThings(dev());
	std::uniform_int_distribution<int> dodge(0, 100);
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


