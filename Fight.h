#pragma once
#include "Vampire.h"
#include "Player.h"
#include "Minotaur.h"
#include "Skeleton.h"
#include "Vampire.h"
#include "Minotaur.h"
#include <string>
#include <Windows.h>
#include <wctype.h>
class Fight
{
private:
	CONST short actionCOORD_X = 24;
	CONST short roundCOORD_X = 37;
	CONST int STALA_INT_KOLORU_TEXTU = 119;;
	CONST int STALA_KOLORU_TEXTU_WALKI = 112;
	CONST int STALA_KOLORU_STATYSTYK = 121;
	CONST int STALA_KOLORU_HP = 113;
	CONST int STALA_KOLORU_UMIEJETNOSCI = 117;
	CONST int STALA_KOLORU_AKCJI = 113;
	CONST int STALA_KOLORU_HIT = 116;
	int round = 0;			//licznik rund
	short actionCOORD_Y = 5; //inkrementacja
	short roundCOORD_Y = 1;		//inkrementacja
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD fightPosition = { actionCOORD_X, actionCOORD_Y };
	COORD roundLoopPosition = { roundCOORD_X, roundCOORD_Y };

	Player player;
	Enemy creature;

	bool isFightEnded();  //warunek konczoncy walke
	void roundLoop();  //inkrementuje runda
	void leadingUI();		//wyswietlna kolumny
	void showUIPlayerEnemy();   //wyswietla statystyki etc.
	void fightPlayerAttack();		 
	void fightCreatureAttack();  
	void setEnergyBar();			 //ustawia wartosc energy baru
	void clearCombat();					// czysci combat co 5rund
	void setHpBar();
	void clearErrorField();				//czysci pole wyboru akcji
	void infoWrongAction();  
	void normalAttack();
public:
	Fight::Fight(Player&, int);  //Flaga int 1 =szkielet,2=minotaur 3=vampire
	bool fightStart();
	~Fight();
};
