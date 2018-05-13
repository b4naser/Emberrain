#pragma once
#include <cstdlib>
#include <random>
#include <string>
class Player
{
private :
	int playerHp,playerStrength,playerDefence,playerEnergy,playerDodgdeRate;
	std::string playerName;

	int playerTurnAttackValue;
public:
	Player();

	void playerDecreaseHP(int damageTaken);
	void playerIncreaseEnergy();
	void playerDecreaseEnergy(int);

	int playerAttack();
	int playerCrushingAttack();

	bool playerDodging(); // gracz unika

	int getPlayerDefence();
	std::string getPlayerName();
	int getPlayerEnergy();
	int getPlayerHP();
	int getPlayerTurnAttackValue()const;
	int getPlayerDodgeRate() const;
	int getPlayerStrength() const;
	void setPlayerName(std::string name);
	~Player();
};
