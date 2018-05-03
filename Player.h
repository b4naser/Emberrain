#ifndef PLAYER_H
#define PLAYER_H
#include <cstdlib>
#include <string>
class Player
{
private :
	int playerHp,playerStrengh,playerDefence,playerEnergy,playerDodgdeRate;
	std::string playerName;

	int playerTurnAttackValue;
public:
	Player();
	~Player();

	void playerDicreaseHP(int damageTaken);
	void playerIncreaseHP();
	void playerIncreaseEnergy();
	void playerDicreaseEnergy(int);

	int playerAttack();
	int playerCrushingAttack();

	bool playerDodging(); // gracz unika

	int getPlayerDefence();
	std::string getPlayerName();
	int getPlayerEnergy();
	int getPlayerHP();
	int getPlayerTurnAttackValue()const;
	int getPlayerDodgeRate() const;
	int getPlayerStrengh() const;
	void setPlayerName(std::string name);
};
#endif // !PLAYER_H
