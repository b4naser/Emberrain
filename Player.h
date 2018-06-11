#pragma once
#include <cstdlib>
#include <random>
#include <string>
#include "Equipment.h"
class Player
{
private:
	int playerHp,           //zdrowie gracza
		playerStrength,     //si�a gracza
		playerDefence,      //obrona gracza
		playerEnergy,       //energia gracza
		playerDodgeRate;    //szansa na unik
	int playerBaseHp,           //bazowa warto�� zdrowia
		playerBaseStrength,     //bazowa warto�� si�y
		playerBaseDefence,      //bazowa warto�� obrony
		playerBaseEnergy,       //bazowa warto�� energi
		playerBaseDodgeRate;    //bazowa warto�� uniku
	std::string playerName;      //nazwa gracza

	int playerTurnAttackValue;      //warto�� ataku w konkretnej turze
public:
	Player();
	Equipment* eq;   //ekwipunek gracza
	void playerDecreaseHP(int damageTaken);  //przyjmuje warto�� obra�e� zadanych przez przeciwnika i odejmuje je od puli zdrowia gracza
	void playerIncreaseEnergy();        //zwi�kszanie energi gracza   
	void playerDecreaseEnergy(int);     //zmniejszanie energi gracza

	int playerAttack();             //gracz atakuje
	int playerCrushingAttack();

	bool playerTryToDodge();        //sprawdza czy gracz wykona� unik

	int getPlayerDefence();         //zwraca obrone (defence) gracza
	std::string getPlayerName();    //zwraca nazw� gracza
	int getPlayerEnergy();          //zwraca energi� gracza
	int getPlayerHP();              //zwraca zdrowie gracza
	int getPlayerTurnAttackValue()const;  //zwraca warto�� ataku w konkretnej turze
	int getPlayerDodgeRate() const;       //zwraca szanse gracza na unik
	int getPlayerStrength() const;        //zwraca si�e gracza
	void setPlayerName(std::string name);  //ustawia nazwe gracza

	void refreshPlayer();           //od�wierza statystyki gracza (do bazowych warto�ci dodaje warto��i z ekwipunku)

	~Player();
};

