#ifndef FIGHT_H
#define FIGHT_H
#include "Surface.h"
#include "Vampire.h"
#include "Player.h"
#include "Minotaur.h"
#include "Skeleton.h"
#include "Vampire.h"
#include "Minotaur.h"
#include <string>
#include <Windows.h>
#include <wctype.h>
//asdsadasdas//
class Fight
{
private:
	CONST short STALA = 24;
	CONST short STALA_RUNDY = 45;
	CONST int STALA_INT_KOLORU_TEXTU = 119;//34;
	CONST int STALA_KOLORU_TEXTU_PLAYERA = 112;
	CONST int STALA_KOLORU_STATYSTYK = 124;
	CONST int STALA_KOLORU_TEXTU_ENEMY = 112;
	CONST int STALA_KOLORU_UMIEJETNOSCI = 117;
	CONST int STALA_KOLORU_AKCJI = 113;
	int runda = 0;
	short rzad_Akcji = 8;
	short rzad_Rundy = 5;
	bool condition = true;   //warunek potrzebny do petli ..wajcha..

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };
	COORD pozycjaPokazywaniaRundy = { STALA_RUNDY, rzad_Rundy };

	Player player;
	Enemy creature;

	bool isFightEnded();  //warunek konczoncy walke
	void roundLoop();  //inkrementuje runda++
	void leadingUI();		//wyswietlna kolumny
	void showUIPlayerEnemy();   //wyswietla statystyki etc.
	void fightPlayerAttack();		 //na potrzeby klasy funckja ataku enemy
	void fightCreatureAttack();   //na potrzeby klasy funckja ataku playera
	void setEnergyBar();			 //ustawia wartosc energy baru
	void clearCombat();					// czysci combat co 5rund
	void setHpBar();					
	void clearChooseField(bool);				//czysci pole wyboru akcji
	void infoBrakWyboru(int);   //bl1ad 1-brak energi 2-brak wlasciwej akcji
	void normalAttack();
							
public:
	Fight::Fight(Player& ,int);  //Flaga int 1 =szkielet,2=minotaur 3=vampire
	void fightStart();
	Surface surface= Surface(100,32);
	~Fight();


};

#endif // !FIGHT_H