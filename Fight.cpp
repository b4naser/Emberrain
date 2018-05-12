#include "Fight.h"
#include <iostream>

using namespace std;

bool Fight::isFightEnded()
{
	if (creature.getCreatureHp() <= 0 || player.getPlayerHP() <= 0) return true;
	else return false;
}

void Fight::roundLoop()
{
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaRundy);  //usawia cursor RUNDY
	runda++;
	cout << "RUNDA " << runda;
	
}


Fight::Fight(Player& play,int FLAGA)
{
	if (FLAGA == 1) {
		player = play;
		creature = Skeleton(play.getPlayerStrengh(), play.getPlayerDefence(), play.getPlayerHP());
		leadingUI();
		showUIPlayerEnemy();
		roundLoop();
	}
	else if (FLAGA == 2) {
		player = play;
		creature = Minotaur(play.getPlayerStrengh(), play.getPlayerDefence(), play.getPlayerHP());
		leadingUI();
		showUIPlayerEnemy();
		roundLoop();
	}
	else if (FLAGA == 3) {
		player = play;
		creature = Vampire(play.getPlayerStrengh(), play.getPlayerDefence(), play.getPlayerHP());
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
			
			if (isFightEnded()) {  //warunek zakonczenia
				setHpBar();  
				return true;
			}             
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
			fightCreatureAttack();
			roundLoop();
			if (isFightEnded()) {   //warunek zakonczenia
				setHpBar();  
				return false;
			}		
			setHpBar();
			rzad_Akcji++;

			if (player.getPlayerEnergy() < 100) {
				player.playerIncreaseEnergy();
				setEnergyBar();
			}
		}
}
void Fight::clearCombat()
{
	short y=5;
	COORD x;
	for (int i = 0; 17>i; i++) {
		x = { STALA, y++ };
		SetConsoleCursorPosition(hConsole, x);
		std::cout << "                                   ";
	}
}
void Fight::clearChooseField(bool tempCondition)
{
	if (tempCondition) {

		pozycjaPokazywaniaAkcji = { 14, 28 };  //KOD:101
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "               ";
		pozycjaPokazywaniaAkcji = { 30, 28 };
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "                                                    ";
	}
	else {
		pozycjaPokazywaniaAkcji = { 14, 28 };  //KOD:101
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "              ";
	}

}
void Fight::infoWrongAction(int FLAG_ERROR)
{
	if (FLAG_ERROR == 1) {
		pozycjaPokazywaniaAkcji = { 30, 28 };
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Brak energii na wykonanie akcji!";
	}
	else if (FLAG_ERROR == 2) {
		pozycjaPokazywaniaAkcji = { 30, 28 };
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Wybrano niewlasciwa akcje! Dostepne akcje 1-2";
		clearChooseField(false);
	}

}
void Fight::normalAttack()
{
	pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	rzad_Akcji++;
	player.playerDicreaseHP(creature.creatureAttack());
	cout << creature.getCreatureName();
	printf(" attacks :%-2d leaving : %3d ",
		creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
}
Fight::~Fight()
{
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
	for (int i = 0; i < 25; i++) {
		temp = { 0,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	//pozioma belka 2
	for (int i = 0; i < 79; i++) {
		std::cout << gora_belka;
	}
	//pion belka 2
	for (int i = 0; i < 25; i++) {
		if (i == 0) rysuj = 0;
		temp = { 22,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	
	//pion belka 3
	for (int i = 0; i < 25; i++) {
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

		pozycjaPokazywaniaAkcji = { 26, 25 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Przegrana!";

		pozycjaPokazywaniaAkcji = { 14, 28 };  //Powrot do pola wyboru zeby kursor nie wariowal
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	}
	else if(creature.getCreatureHp()<=0) {

		temporary = { 71, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy
		SetConsoleCursorPosition(hConsole, temporary);   //czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.
		cout << "    ";
		temporary = { 73, positionEnemyHPbarY };    //recznie wpisane cordy hp baru enemy
		SetConsoleCursorPosition(hConsole, temporary);
		cout << "0";							//czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.

		pozycjaPokazywaniaAkcji = { 32, 25 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Wygrana!Zdobywasz " << 12 << " krysztalow";

		pozycjaPokazywaniaAkcji = { 14, 28 };  //Powrot do pola wyboru zeby kursor nie wariowal
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	}
	else {

		temporary = { 12,  positionPlayerHPbarY };
		SetConsoleCursorPosition(hConsole, temporary);
		cout << "    ";

		if (player.getPlayerHP() >100)
			temporary = { 12,  positionPlayerHPbarY };
		else if (player.getPlayerHP() <100 && player.getPlayerHP() >10)
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
		else if (creature.getCreatureHp() <100 && creature.getCreatureHp() > 10)
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

	pozycjaPokazywaniaAkcji = { 25,  2 };		
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << player.getPlayerName() << "      vs       " << creature.getCreatureName();

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Nazwa: " << creature.getCreatureName();
	tempCreatureY += 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Statystyki:";
	tempCreatureY+=1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY  };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Zycie: %5d", creature.getCreatureHp()); 
	//IMPORTANT_COORD_HPBAR_PLAYER_X = tempCreatureX;
	//IMPORTANT_COORD_HPBAR_PLAYER_Y = tempCreatureY;
	tempCreatureY += 1;


	pozycjaPokazywaniaAkcji = { tempCreatureX, tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Atak: %6d", creature.getCreatureStrengh());
	tempCreatureY += 1;

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Obrona: %4d", creature.getCreatureDefence());
	tempCreatureY += 4;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_UMIEJETNOSCI);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Umiejetnosci:");
	tempCreatureY += 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout<<"Unik: "<<creature.getCreatureDodgeRate()<<"%";
	tempCreatureY += 1;

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Ogluszenie: " << creature.getCreatureStunRate() << "%";
	tempCreatureY += 1;

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Life Steal: " << creature.getCreatureLifeStealingRate() << "%";
	tempCreatureY += 1;

	////////////////////////////
	// player
	///////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Nazwa: " << player.getPlayerName();
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Statystyki:");
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Zycie:  %4d", player.getPlayerHP());
	tempPlayerY = tempPlayerY + 1;

	pozycjaPokazywaniaAkcji = { tempPlayerX, tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Energia: %3d", player.getPlayerEnergy());
	tempPlayerY = tempPlayerY + 1;

	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Atak: %6d", player.getPlayerStrengh());
	tempPlayerY = tempPlayerY + 1;

	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Obrona: %4d", player.getPlayerDefence());
	tempPlayerY=tempPlayerY+2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_UMIEJETNOSCI);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Umiejetnosci: ");
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Regeneracja: +5E");
	tempPlayerY = tempPlayerY + 1;

	
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout <<"Unik: "  << player.getPlayerDodgeRate() << "%";
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_AKCJI);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Akcje:  ";
	tempPlayerY = tempPlayerY + 1;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "1)Atak(K:0)";
	tempPlayerY = tempPlayerY + 1;


	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "2)Pchniecie(K:20)";
	tempPlayerY = tempPlayerY + 1;

	pozycjaPokazywaniaAkcji = { 0, 27 };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Rozpoczela sie walka pomiedzy " << player.getPlayerName() << " a " << creature.getCreatureName();
	pozycjaPokazywaniaAkcji = { 0, 28 };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Wybierz akcje: ";
}

void Fight::fightPlayerAttack()
{

	int option;		// wybor playera
	char ch;	    //w razie bledu
	clearChooseField(true);
	while (1) {
		pozycjaPokazywaniaAkcji = {14, 28 };  //KOD:101
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		if (scanf_s("%d", &option) != 1) {
			while (ch = getchar() != '\n');
			infoWrongAction(2);
			Sleep(100);
		}
		else if(option<=2) {

			  //inkrementacja rundy
			if (runda % 5 == 0) {
				clearCombat();
				rzad_Akcji = 5;//WARNING TU TEZ ZMIEN!
				pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };
                      
			}

				switch (option) 
					{
					case 1:
						if (creature.creatureDodge()) {
							pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
							rzad_Akcji++;
							cout << creature.getCreatureName() << " dodging !";
							clearChooseField(true);
							break;
						}
						creature.creatureHpDicrease(player.playerAttack());

						pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
						SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
						rzad_Akcji++;

						cout << player.getPlayerName();
						printf(" attacks :%-2d leaving : %3d ",
							player.getPlayerTurnAttackValue() - creature.getCreatureDefence(), creature.getCreatureHp());
						clearChooseField(true);
						break;
					case 2:
						if (creature.creatureDodge()) {
							pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
							rzad_Akcji++;
							cout << creature.getCreatureName() << " dodging!";
							if (player.getPlayerEnergy() >= 50) {
								player.playerDicreaseEnergy(10);
								setEnergyBar();
							}
							clearChooseField(true);
							break;
						}
						if (player.getPlayerEnergy() >= 50) {
							player.playerDicreaseEnergy(20);
							creature.creatureHpDicrease( player.playerCrushingAttack() );
							pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
							rzad_Akcji++;
							cout << player.getPlayerName();
							printf(" attacks :%-2d leaving : %3d ",
								player.getPlayerTurnAttackValue() - creature.getCreatureDefence(), creature.getCreatureHp());
							setEnergyBar();
							clearChooseField(true);
							break;
						}
						else {
								infoWrongAction(1);
								clearChooseField(false);
								continue;
							}
					}
				break;
		}
		else infoWrongAction(2);  //1 -brak energi 2-niewlasciwa akcja
	}
}
void Fight::fightCreatureAttack() {
	
	if (player.playerDodging())
	{
		pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		rzad_Akcji++;
		cout << "Dodges!";
		return;
	}
	else if ( (creature.getCreatureStunRate() > 0) && creature.creatureTryStun() ) 
	{
			pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
			SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
			rzad_Akcji++;
			rzad_Akcji++;

			player.playerDicreaseHP(creature.creatureAttack());
			cout << creature.getCreatureName();
			printf(" attacks :%-2d leaving : %3d ",
				creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
			pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
			SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
			rzad_Akcji++;
			cout << "Stunning!";
			normalAttack();

	}
	else if ( (creature.getCreatureLifeStealingRate() > 0) && creature.creatureReturningLife() ) {
			if (creature.getCreatureHp() < 120) 
			{
				pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
				SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
				rzad_Akcji++;
				player.playerDicreaseHP(creature.creatureAttack());
				cout << creature.getCreatureName();
				printf(" attacks :%-2d leaving : %3d ",
					creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
				creature.creatureTryLifeStealing(player.getPlayerDefence());
				pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
				SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
				rzad_Akcji++;
				cout << "Wampir healing himself for " << creature.getCreatureTurnAttackValue()-player.getPlayerDefence();
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
	else if(player.getPlayerEnergy() < 100 && player.getPlayerEnergy()>10)
		xy = { 13,  6 };
	else if (player.getPlayerEnergy() < 10)
		xy = { 14,  6 };
	SetConsoleCursorPosition(hConsole, xy);

	cout << player.getPlayerEnergy();
}
