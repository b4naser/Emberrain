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
	CONST short actionCOORD_X = 24;   //stala wartosc wsp�rz�dnej X fightPosition
	CONST short roundCOORD_X = 37;		//stala wartosc wsp�rz�dnej X roundLoopPosition

	// Poszczeg�lne wartosci sta�e kolor�w
	CONST int STALA_INT_KOLORU_TEXTU = 119;;    
	CONST int STALA_KOLORU_TEXTU_WALKI = 112;
	CONST int STALA_KOLORU_STATYSTYK = 121;
	CONST int STALA_KOLORU_HP = 113;
	CONST int STALA_KOLORU_UMIEJETNOSCI = 117;
	CONST int STALA_KOLORU_AKCJI = 113;
	CONST int STALA_KOLORU_HIT = 116;

	int round = 0;			//licznik rund
	short actionCOORD_Y = 6; //poczatkowa wartosc wsp�rz�dnej Y fightPosition
	short roundCOORD_Y = 1;		//poczatkowa wartosc wsp�rz�dnej Y roundLoopPosition

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);        
	COORD fightPosition = { actionCOORD_X, actionCOORD_Y };      //pozycja wsp�rz�dnych wykonywanych akcji w consoli
	COORD roundLoopPosition = { roundCOORD_X, roundCOORD_Y };    //pozycja wsp�rz�dnych rundy w consoli

	Player player;
	Enemy creature;   

	bool isFightEnded();	//warunek konczoncy walke gracz albo przeciwnik nie posiadaja juz zdrowia
	void roundLoop();			//inkrementuje runde
	void leadingUI();		//wy�wietla kolumny,tlo
	void showUIPlayerEnemy();   //wyswietla statystyki gracza i przeciwnika na bocznych panelach.
	void fightPlayerAttack();		//funckja w ktorej gracz ma mozliwosc wybrania akcji  
	void fightCreatureAttack();    // przeciwnik wykonuje swoj ruch
	void setEnergyBar();			 //ustawia aktualna wartosc energii gracza
	void clearCombat();					// czysci srodkowe pole UI co 5rund
	void setHpBar();					//ustawia aktualna warto�� �ycia przeciwnika i gracza
	void clearErrorField();				//czy�ci pole komunikatu po wybraniu prawidlowej opcji
	void infoWrongAction();				//wyswietla komunikat o bl�dzie
	void normalAttack();				//funckja pomocnicza na potrzeby funkcji fightCreatureAttack
public:
	Fight::Fight(Player&, int);  //int id 1 =szkielet,2=minotaur 3=vampire
	bool fightStart();					//rozpoczecie walki
	~Fight();
};
