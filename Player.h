#pragma once
#include <cstdlib>
#include <random>
#include <string>
#include "Equipment.h"
class Player
{
private:
	int playerHp,           //zdrowie gracza
		playerStrength,     //si³a gracza
		playerDefence,      //obrona gracza
		playerEnergy,       //energia gracza
		playerDodgeRate;    //szansa na unik
	int playerBaseHp,           //bazowa wartoœæ zdrowia
		playerBaseStrength,     //bazowa wartoœæ si³y
		playerBaseDefence,      //bazowa wartoœæ obrony
		playerBaseEnergy,       //bazowa wartoœæ energi
		playerBaseDodgeRate;    //bazowa wartoœæ uniku
	std::string playerName;      //nazwa gracza

	int playerTurnAttackValue;      //wartoœæ ataku w konkretnej turze
public:
	Player();
	Equipment* eq;   //ekwipunek gracza
	void playerDecreaseHP(int damageTaken);  //przyjmuje wartoœæ obra¿eñ zadanych przez przeciwnika i odejmuje je od puli zdrowia gracza
	void playerIncreaseEnergy();        //zwiêkszanie energi gracza   
	void playerDecreaseEnergy(int);     //zmniejszanie energi gracza

	int playerAttack();             //gracz atakuje
	int playerCrushingAttack();

	bool playerTryToDodge();        //sprawdza czy gracz wykona³ unik

	int getPlayerDefence();         //zwraca obrone (defence) gracza
	std::string getPlayerName();    //zwraca nazwê gracza
	int getPlayerEnergy();          //zwraca energiê gracza
	int getPlayerHP();              //zwraca zdrowie gracza
	int getPlayerTurnAttackValue()const;  //zwraca wartoœæ ataku w konkretnej turze
	int getPlayerDodgeRate() const;       //zwraca szanse gracza na unik
	int getPlayerStrength() const;        //zwraca si³e gracza
	void setPlayerName(std::string name);  //ustawia nazwe gracza

	void refreshPlayer();           //odœwierza statystyki gracza (do bazowych wartoœci dodaje wartoœæi z ekwipunku)

	~Player();
};

