#include "Fight.h"
#include <iostream>
#include <conio.h>
using namespace std;

bool Fight::isFightEnded()
{
	if (creature.getCreatureHp() <= 0 || player.getPlayerHP() <= 0) return true;
	else return false;
}

void Fight::roundLoop()
{
	SetConsoleCursorPosition(hConsole, roundLoopPosition);  //usawia cursor RUNDY
	round++;
	cout << "RUNDA " << round;
	
}


Fight::Fight(Player& play,int FLAGA)
{
	if (FLAGA == 1) {
		player = play;
		creature = Skeleton(play.getPlayerStrength(), play.getPlayerDefence(), play.getPlayerHP());
		leadingUI();
		showUIPlayerEnemy();
		roundLoop();
	}
	else if (FLAGA == 2) {
		player = play;
		creature = Minotaur(play.getPlayerStrength(), play.getPlayerDefence(), play.getPlayerHP());
		leadingUI();
		showUIPlayerEnemy();
		roundLoop();
	}
	else if (FLAGA == 3) {
		player = play;
		creature = Vampire(play.getPlayerStrength(), play.getPlayerDefence(), play.getPlayerHP());
		leadingUI();
		showUIPlayerEnemy();
		roundLoop();
	}

	else {
		cout << "Podano klase, ktorej nie ma w bazie "
			<< endl;
	}
}
bool Fight::fightStart()
{

		while (true) {
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
			fightPlayerAttack();
			
			if (isFightEnded()) 
			{  //warunek zakonczenia
				setHpBar();  
				return true;
			}             
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
			fightCreatureAttack();
			roundLoop();
			if (isFightEnded())
			{   //warunek zakonczenia
				setHpBar();  
				return false;
			}		
			setHpBar();
			actionCOORD_Y++;
			if (player.getPlayerEnergy() < 100) {
				player.playerIncreaseEnergy();
				setEnergyBar();
			}
		}
}
Fight::~Fight()
{
}
void Fight::clearCombat()
{
	short y=5;
	COORD x;
	for (int i = 0; 17>i; i++) {
		x = { actionCOORD_X, y++ };
		SetConsoleCursorPosition(hConsole, x);
		std::cout << "                                   ";
	}
}
void Fight::clearChooseField(bool tempCondition)
{
	if (tempCondition) {

		fightPosition = { 14, 28 };  //KOD:101
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "               ";
		fightPosition = { 30, 28 };
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "                                                    ";
	}
	else {
		fightPosition = { 14, 28 };  //KOD:101
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "              ";
	}

}
void Fight::infoWrongAction(int FLAG_ERROR)
{
	if (FLAG_ERROR == 1) {
		fightPosition = { 30, 28 };
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "Niewystatrczajaco energii!";
	}
	else if (FLAG_ERROR == 2) {
		fightPosition = { 30, 28 };
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "Wybierz prawidlowa akcje!";
	}

}
void Fight::normalAttack()
{
	fightPosition = { actionCOORD_X, actionCOORD_Y };				
	SetConsoleCursorPosition(hConsole, fightPosition);
	actionCOORD_Y++;
	player.playerDecreaseHP(creature.creatureAttack());
	cout << creature.getCreatureName();
	printf(" atakuje:%d zostawiajac:%d",
		creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
}

void Fight::leadingUI()
{
	COORD temp = { 0,0 };

	std::string pion_belka = " ";
	std::string gora_belka = " ";
	std::string mapa = "        ";

	short rysuj = 0;  //zmienna do chodzenia kursorem

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_INT_KOLORU_TEXTU);
	for (int i = 0; i < 630; i++) {
		std::cout << mapa;
	}

	SetConsoleCursorPosition(hConsole, temp);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | BACKGROUND_RED);

	temp = { 0,0 };
	//pozioma belka 1
	SetConsoleCursorPosition(hConsole, temp);
	for (int i = 0; i < 79; i++) {
		std::cout << gora_belka;
	}
	//pion belka 1
	for (int i = 0; i < 26; i++) {
		temp = { 0,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	//pozioma belka 2
	for (int i = 0; i < 79; i++) {
		std::cout << gora_belka;
	}
	//pion belka 2
	for (int i = 0; i < 26; i++) {
		if (i == 0) rysuj = 0;
		temp = { 22,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	
	//pion belka 3
	for (int i = 0; i < 26; i++) {
		if (i == 0) rysuj = 0;
		temp = { 60,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	
	//pion belka 4
	for (int i = 0; i < 25; i++) {
		if (i == 0) rysuj = 0;
		temp = { 79,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	
}
void Fight::setHpBar()
{
	short positionPlayerHPbarY = 5;
	short positionEnemyHPbarY = 5;

	COORD temporary = { 14,  positionPlayerHPbarY };  //recznie wpisane cordy hp baru gracza
	if (player.getPlayerHP() <= 0) {
		temporary = { 12,  positionPlayerHPbarY };
		SetConsoleCursorPosition(hConsole, temporary);  //czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci./start
		cout << "    ";
		temporary = { 14,  positionPlayerHPbarY };
		SetConsoleCursorPosition(hConsole, temporary);
		cout << "0";							//czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci/end

		fightPosition = { 25, 24 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "Przegrana!";

		fightPosition = { 14, 28 };  //Powrot do pola wyboru zeby kursor nie wariowal
		SetConsoleCursorPosition(hConsole, fightPosition);
	}
	else if(creature.getCreatureHp()<=0) {

		temporary = { 71, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy
		SetConsoleCursorPosition(hConsole, temporary);   //czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.
		cout << "    ";
		temporary = { 73, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy
		SetConsoleCursorPosition(hConsole, temporary);
		cout << "0";							//czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.

		fightPosition = { 25, 24 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "Wygrana!Zdobywasz " << rand()%20 << " krysztalow";

		fightPosition = { 14, 28 };  //Powrot do pola wyboru zeby kursor nie wariowal
		SetConsoleCursorPosition(hConsole, fightPosition);
	}
	else {

		temporary = { 12,  positionPlayerHPbarY };
		SetConsoleCursorPosition(hConsole, temporary);
		cout << "    ";

		if (player.getPlayerHP() >100)
			temporary = { 12,  positionPlayerHPbarY };
		else if (player.getPlayerHP() <100 && player.getPlayerHP() >=10)
			temporary = { 13,  positionPlayerHPbarY };
		else if (player.getPlayerHP() <10)
			temporary = { 14,  positionPlayerHPbarY };

		SetConsoleCursorPosition(hConsole, temporary);
		cout << player.getPlayerHP();

		temporary = { 71, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy

		SetConsoleCursorPosition(hConsole, temporary);
		cout << "    ";

		if (creature.getCreatureHp() >= 100)
			temporary = { 71, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy
		else if (creature.getCreatureHp() <100 && creature.getCreatureHp() >= 10)
			temporary = { 72, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy
		else if (creature.getCreatureHp() <10)
			temporary = { 73, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy

		SetConsoleCursorPosition(hConsole, temporary);
		cout << creature.getCreatureHp();
	}

}
void Fight::showUIPlayerEnemy()
{
	
	short tempCreatureX = 62;
	short tempPlayerX = 3;
	short tempPlayerY = 2;
	short tempCreatureY = 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);


	///////////////////////////////////
	// Enemy
	///////////////////////////////////

	fightPosition = { 25,  2 };		
	SetConsoleCursorPosition(hConsole, fightPosition);
	//cout << player.getPlayerName() << "      vs       " << creature.getCreatureName();

	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Nazwa: " << creature.getCreatureName();
	tempCreatureY += 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Statystyki:";
	tempCreatureY+=1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
	fightPosition = { tempCreatureX,  tempCreatureY  };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Zycie: %5d", creature.getCreatureHp()); 
	//IMPORTANT_COORD_HPBAR_PLAYER_X = tempCreatureX;
	//IMPORTANT_COORD_HPBAR_PLAYER_Y = tempCreatureY;
	tempCreatureY += 1;


	fightPosition = { tempCreatureX, tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Atak: %6d", creature.getCreatureStrength());
	tempCreatureY += 1;

	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Obrona: %4d", creature.getCreatureDefence());
	tempCreatureY += 4;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_UMIEJETNOSCI);
	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Umiejetnosci:");
	tempCreatureY += 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout<<"Unik: "<<creature.getCreatureDodgeRate()<<"%";
	tempCreatureY += 1;

	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Ogluszenie: " << creature.getCreatureStunRate() << "%";
	tempCreatureY += 1;

	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Life Steal: " << creature.getCreatureLifeStealRate() << "%";
	tempCreatureY += 1;

	////////////////////////////
	// player
	///////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Nazwa: " << player.getPlayerName();
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Statystyki:");
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Zycie:  %4d", player.getPlayerHP());
	tempPlayerY = tempPlayerY + 1;

	fightPosition = { tempPlayerX, tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Energia: %3d", player.getPlayerEnergy());
	tempPlayerY = tempPlayerY + 1;

	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Atak: %6d", player.getPlayerStrength());
	tempPlayerY = tempPlayerY + 1;

	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Obrona: %4d", player.getPlayerDefence());
	tempPlayerY=tempPlayerY+2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_UMIEJETNOSCI);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Umiejetnosci: ");
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Regeneracja: +5E");
	tempPlayerY = tempPlayerY + 1;

	
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout <<"Unik: "  << player.getPlayerDodgeRate() << "%";
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_AKCJI);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Akcje:  ";
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "1)Atak(K:0)";
	tempPlayerY = tempPlayerY + 1;


	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "2)Pchniecie(K:20)";
	tempPlayerY = tempPlayerY + 1;

	fightPosition = { 0, 27 };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Rozpoczela sie walka pomiedzy " << player.getPlayerName() << " a " << creature.getCreatureName();
	fightPosition = { 0, 28 };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Wybierz akcje: ";
}

void Fight::fightPlayerAttack()
{

	char ch;	    //w razie bledu
	while (1)
	{
		fightPosition = {14, 28 };  //KOD:101
		SetConsoleCursorPosition(hConsole, fightPosition);
		ch = getch();
		 
		if (round % 5 == 0)
		{
			clearCombat();
			actionCOORD_Y = 5;//WARNING TU TEZ ZMIEN!
			fightPosition = { actionCOORD_X, actionCOORD_Y };
		}
				switch (ch) 
					{
					case '1':
						if (creature.creatureDodge()) 
						{
							fightPosition = { actionCOORD_X, actionCOORD_Y };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, fightPosition);
							actionCOORD_Y++;
							cout << creature.getCreatureName() << " unika ataku!";
						}
						else 
						{
							creature.creatureHpDecrease(player.playerAttack());
							fightPosition = { actionCOORD_X, actionCOORD_Y };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, fightPosition);
							actionCOORD_Y++;
							cout << player.getPlayerName();
							printf(" atakuje:%d zostawiajac:%d",
								player.getPlayerTurnAttackValue()-creature.getCreatureDefence(), creature.getCreatureHp());
						}
						break;
					case '2':
						if (player.getPlayerEnergy()<20) 
						{
							infoWrongAction(1);
							continue;
						}
						else if (creature.creatureDodge()) 
						{
							player.playerDecreaseEnergy(20);
							fightPosition = { actionCOORD_X, actionCOORD_Y };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, fightPosition);
							actionCOORD_Y++;
							cout << creature.getCreatureName() << " unika ataku!";
							setEnergyBar();
						}
						else 
						{
							player.playerDecreaseEnergy(20);
							fightPosition = { actionCOORD_X, actionCOORD_Y };		//usawia cursor AKCJI
							creature.creatureHpDecrease( player.playerCrushingAttack() );
							SetConsoleCursorPosition(hConsole, fightPosition);
							actionCOORD_Y++;
							cout << player.getPlayerName();
							printf(" atakuje:%d zostawiajac:%d",
							player.getPlayerTurnAttackValue() - creature.getCreatureDefence(), creature.getCreatureHp());
							setEnergyBar();
						}
						break;
					default:
						infoWrongAction(2);
						continue;
					}
				break;
	}

}
void Fight::fightCreatureAttack() {
	
	if (player.playerDodging())
	{
		fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
		SetConsoleCursorPosition(hConsole, fightPosition);
		actionCOORD_Y++;
		cout <<player.getPlayerName()<< " unika ataku!";
	}
	else if ( (creature.getCreatureStunRate() > 0) && creature.creatureTryStun()) 
	{
			fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
			SetConsoleCursorPosition(hConsole, fightPosition);
			actionCOORD_Y++;
			actionCOORD_Y++;
			player.playerDecreaseHP(creature.creatureAttack());
			cout << creature.getCreatureName();
			printf(" atakuje:%d zostawiajac:%d",
				creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
			fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
			SetConsoleCursorPosition(hConsole, fightPosition);
			actionCOORD_Y++;
			cout << "Ogluszenie!";
			roundLoop();
			normalAttack();
	}
	else if ( (creature.getCreatureLifeStealRate() > 0) && creature.creatureReturningLife() )
	{
			if (creature.getCreatureHp() < 120) 
			{
				fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
				SetConsoleCursorPosition(hConsole, fightPosition);
				actionCOORD_Y++;
				player.playerDecreaseHP(creature.creatureAttack());
				cout << creature.getCreatureName();
				printf(" atakuje:%d zostawiajac:%d",
					creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
				creature.creatureTryLifeSteal(player.getPlayerDefence());
				fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
				SetConsoleCursorPosition(hConsole, fightPosition);
				actionCOORD_Y++;
				cout << "Wampir leczy sie za " << creature.getCreatureTurnAttackValue()-player.getPlayerDefence();
			}
			else normalAttack();
	}
	else normalAttack();

}

void Fight::setEnergyBar()
{
	COORD xy = { 12,  6 };
	SetConsoleCursorPosition(hConsole, xy);
	cout << "   ";
	if(player.getPlayerEnergy() == 100)
		xy = { 12,  6 };
	else if(player.getPlayerEnergy() < 100 && player.getPlayerEnergy()>=10)
		xy = { 13,  6 };
	else if (player.getPlayerEnergy() < 10)
		xy = { 14,  6 };
	SetConsoleCursorPosition(hConsole, xy);
	cout << player.getPlayerEnergy();
}
