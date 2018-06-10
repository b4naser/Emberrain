#pragma once
#include <cstdlib>
#include <random>
#include <string>
#include "Equipment.h"
class Player
{
private :
	int playerHp,playerStrength,playerDefence,
		playerEnergy,playerDodgeRate;
	int playerBaseHp, playerBaseStrength, playerBaseDefence,
		playerBaseEnergy, playerBaseDodgeRate;
	std::string playerName;

	int playerTurnAttackValue;
public:
	Player();
	Equipment* eq;
	void playerDecreaseHP(int damageTaken);
	void playerIncreaseEnergy();
	void playerDecreaseEnergy(int);

	int playerAttack();
	int playerCrushingAttack();

	bool playerTryToDodge(); 

	int getPlayerDefence();
	std::string getPlayerName();
	int getPlayerEnergy();
	int getPlayerHP();
	int getPlayerTurnAttackValue()const;
	int getPlayerDodgeRate() const;
	int getPlayerStrength() const;
	void setPlayerName(std::string name);

	void refreshPlayer();

	~Player();
};
