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


Fight::Fight(Player& play, int FLAGA)
{
	system("cls");
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

}
bool Fight::fightStart()
{

	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
		fightPlayerAttack();
		setHpBar();
		if (isFightEnded())
		{  //warunek zakonczenia
			getchar();
			getchar();
			return true;
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
		fightCreatureAttack();
		setHpBar();
		if (isFightEnded())
		{   //warunek zakonczenia
			getchar();
			getchar();
			return false;
		}
		actionCOORD_Y++;
		roundLoop();
	}
}
Fight::~Fight()
{
}
void Fight::clearCombat()
{
	//czysci okno walki 
	short y = 5;
	COORD x;
	for (int i = 0; 20>i; i++) {
		x = { actionCOORD_X, y++ };
		SetConsoleCursorPosition(hConsole, x);
		std::cout << "                                    ";
	}
}
void Fight::clearChooseField()
{
	//czysci tekst ktory pokazuje brak energii
	fightPosition = { 30, 28 };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "                                            ";

}
void Fight::infoWrongAction()
{
	fightPosition = { 30, 28 };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Niewystatrczajaco energii!";
}
void Fight::normalAttack()
{
	fightPosition = { actionCOORD_X, actionCOORD_Y };
	SetConsoleCursorPosition(hConsole, fightPosition);
	actionCOORD_Y++;
	player.playerDecreaseHP(creature.creatureAttack());
	cout << creature.getCreatureName();
	cout << " atakuje:";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HIT);
	if (creature.getCreatureTurnAttackValue() - player.getPlayerDefence() > 0)
		cout << creature.getCreatureTurnAttackValue() - player.getPlayerDefence();
	else
		cout << "0";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
	cout << " zostawiajac:";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HP);
	cout << player.getPlayerHP();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
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
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HP);
		fightPosition = { 37,3 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "Przegrana!";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_INT_KOLORU_TEXTU);
		fightPosition = { 14, 28 };  //Powrot do pola wyboru 
		SetConsoleCursorPosition(hConsole, fightPosition);
	}
	else if (creature.getCreatureHp() <= 0) {

		temporary = { 71, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy
		SetConsoleCursorPosition(hConsole, temporary);   //czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.
		cout << "    ";
		temporary = { 73, positionEnemyHPbarY };
		SetConsoleCursorPosition(hConsole, temporary);
		cout << "0";							//czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HP);
		fightPosition = { 37, 3 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, fightPosition);
		cout << "Wygrana!";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_INT_KOLORU_TEXTU);
		fightPosition = { 14, 28 };  //Powrot do pola wyboru 
		SetConsoleCursorPosition(hConsole, fightPosition);
	}
	else {

		temporary = { 12,  positionPlayerHPbarY };
		SetConsoleCursorPosition(hConsole, temporary);
		cout << "    ";

		if (player.getPlayerHP() >100)
			temporary = { 12,  positionPlayerHPbarY };
		else if (player.getPlayerHP() <100 && player.getPlayerHP() >= 10)
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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);


	///////////////////////////////////
	// Enemy
	///////////////////////////////////

	fightPosition = { 25,  2 };
	SetConsoleCursorPosition(hConsole, fightPosition);

	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Nazwa: " << creature.getCreatureName();
	tempCreatureY += 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Statystyki:";
	tempCreatureY += 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Zycie: %5d", creature.getCreatureHp());
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

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
	fightPosition = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Unik: " << creature.getCreatureDodgeRate() << "%";
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Nazwa: " << player.getPlayerName();
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Statystyki:");
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
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
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_UMIEJETNOSCI);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Umiejetnosci: ");
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	printf("Regeneracja: +5E");
	tempPlayerY = tempPlayerY + 1;


	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Unik: " << player.getPlayerDodgeRate() << "%";
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_AKCJI);
	fightPosition = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, fightPosition);
	cout << "Akcje:  ";
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
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

	char option;
	while (true)
	{
		fightPosition = { 14, 28 };  //KOD:101
		SetConsoleCursorPosition(hConsole, fightPosition);
		option = getch();

		switch (option)
		{
		case '1':
			if (round % 5 == 0)
			{
				clearCombat();
				actionCOORD_Y = 5;
				fightPosition = { actionCOORD_X, actionCOORD_Y };
			}
			clearChooseField();
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
				cout << " atakuje:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HIT);
				if (player.getPlayerTurnAttackValue() - creature.getCreatureDefence() > 0)
					cout << player.getPlayerTurnAttackValue() - creature.getCreatureDefence();
				else
					cout << "0";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
				cout<<" zostawiajac:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HP);
				cout << creature.getCreatureHp();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
			}
			break;
		case '2':
			if (round % 5 == 0)
			{
				clearCombat();
				actionCOORD_Y = 5;
				fightPosition = { actionCOORD_X, actionCOORD_Y };
			}
			clearChooseField();
			if (player.getPlayerEnergy()<20)
			{
				infoWrongAction();
				continue;
			}
			else if (creature.creatureDodge())
			{
				player.playerDecreaseEnergy(20);
				fightPosition = { actionCOORD_X, actionCOORD_Y };		//usawia cursor AKCJI
				SetConsoleCursorPosition(hConsole, fightPosition);
				actionCOORD_Y++;
				cout << creature.getCreatureName() << " unika ataku!";
			}
			else
			{
				player.playerDecreaseEnergy(20);
				fightPosition = { actionCOORD_X, actionCOORD_Y };		//usawia cursor AKCJI
				creature.creatureHpDecrease(player.playerCrushingAttack());
				SetConsoleCursorPosition(hConsole, fightPosition);
				actionCOORD_Y++;
				cout << player.getPlayerName();
				cout << " atakuje:";
				
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HIT);
				if (player.getPlayerTurnAttackValue() - creature.getCreatureDefence() > 0)
					cout << player.getPlayerTurnAttackValue() - creature.getCreatureDefence();
				else
					cout << "0";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
				cout << " zostawiajac:";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HP);
				cout << creature.getCreatureHp();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
			}
			break;
		default:
			continue;
		}
		player.playerIncreaseEnergy();
		setEnergyBar();
		break;
	}

}
void Fight::fightCreatureAttack() {

	if (player.playerDodging())
	{
		fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
		SetConsoleCursorPosition(hConsole, fightPosition);
		actionCOORD_Y++;
		cout << player.getPlayerName() << " unika ataku!";
	}
	else if ((creature.getCreatureStunRate() > 0) && creature.creatureTryStun())
	{
		fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
		SetConsoleCursorPosition(hConsole, fightPosition);
		actionCOORD_Y++;
		actionCOORD_Y++;
		player.playerDecreaseHP(creature.creatureAttack());
		cout << creature.getCreatureName();

		cout << " atakuje:";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HIT);
		if (creature.getCreatureTurnAttackValue() - player.getPlayerDefence() > 0)
			cout << creature.getCreatureTurnAttackValue() - player.getPlayerDefence();
		else
			cout << "0";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
		cout << " zostawiajac:";
		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HP);
		 cout << player.getPlayerHP();
		 SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
		fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
		SetConsoleCursorPosition(hConsole, fightPosition);
		actionCOORD_Y++;
		cout << "Ogluszenie!";
		roundLoop();
		normalAttack();
	}
	else if ((creature.getCreatureLifeStealRate() > 0) && creature.creatureReturningLife())
	{
		if (creature.getCreatureHp() < 120)
		{
			fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
			SetConsoleCursorPosition(hConsole, fightPosition);
			actionCOORD_Y++;
			player.playerDecreaseHP(creature.creatureAttack());
			cout << creature.getCreatureName();
			cout << " atakuje:";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HIT);
			if (creature.getCreatureTurnAttackValue() - player.getPlayerDefence() > 0)
				cout << creature.getCreatureTurnAttackValue() - player.getPlayerDefence();
			else
				cout << "0";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
			cout << " zostawiajac:";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HP);
			cout << player.getPlayerHP();
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
			creature.creatureTryLifeSteal(player.getPlayerDefence());
			fightPosition = { actionCOORD_X, actionCOORD_Y };					//usawia cursor
			SetConsoleCursorPosition(hConsole, fightPosition);
			actionCOORD_Y++;
			if (creature.getCreatureTurnAttackValue() - player.getPlayerDefence() > 0) {
				cout << "Wampir leczy sie za ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_HIT);
				cout << creature.getCreatureTurnAttackValue() - player.getPlayerDefence();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_AKCJI);
			}
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
	if (player.getPlayerEnergy() >= 100)
		xy = { 12,  6 };
	else if (player.getPlayerEnergy() < 100 && player.getPlayerEnergy() >= 10)
		xy = { 13,  6 };
	else if (player.getPlayerEnergy() < 10)
		xy = { 14,  6 };
	SetConsoleCursorPosition(hConsole, xy);
	cout << player.getPlayerEnergy();
}
