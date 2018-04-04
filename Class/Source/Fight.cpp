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
	cout << "RUNDA " << runda+1;
	runda++;
}


Fight::Fight(Player& play,int FLAGA)
{
	if (FLAGA == 1) {
		player = play;
		creature = Skeleton();
		fightStart();
	}
	else if (FLAGA == 2) {
		player = play;
		creature = Minotaur();
		fightStart();
	}
	else if (FLAGA == 3) {
		player = play;
		creature = Vampire();
		fightStart();
	}
	else {
		cout << "Podano klase, ktorej nie ma w bazie "
			<< endl;
	}

}


void Fight::fightStart()
{
		leadingUI();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		showUIPlayerEnemy();
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_INT_KOLORU_TEXTU);
		roundLoop();
		while (true) {

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
			fightPlayerAttack();
			
			if (isFightEnded()) {  //warunek zakonczenia
				setHpBar();  
				break;
			}             
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
			fightCreatureAttack();

			if (isFightEnded()) {   //warunek zakonczenia
				setHpBar();  
				break;
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
	short y=8;
	COORD x;
	for (int i = 8; rzad_Akcji+1 > i; i++) {
		x = { STALA, y++ };
		SetConsoleCursorPosition(hConsole, x);
		std::cout << "                                                 ";
	}
}



void Fight::clearChooseField(bool tempCondition)
{
	if (tempCondition) {

		pozycjaPokazywaniaAkcji = { 14, 31 };  //KOD:101
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "               ";
		pozycjaPokazywaniaAkcji = { 30, 31 };
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "                                                    ";
	}
	else {
		pozycjaPokazywaniaAkcji = { 14, 31 };  //KOD:101
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "       ";
	}

}

void Fight::infoBrakWyboru(int FLAG_ERROR)
{
	if (FLAG_ERROR == 1) {
		pozycjaPokazywaniaAkcji = { 30, 31 };
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Brak energii na wykonanie akcji!";
	}
	else if (FLAG_ERROR == 2) {
		pozycjaPokazywaniaAkcji = { 30, 31 };
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Wybrano niewlasciwa akcje! Dostepne akcje 1-5";
	}

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
	for (int i = 0; i < 100; i++) {
		std::cout << gora_belka;
	}
	//pion belka 1
	for (int i = 0; i < 30; i++) {
		temp = { 0,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	//pozioma belka 2
	for (int i = 0; i < 100; i++) {
		std::cout << gora_belka;
	}
	//pion belka 2
	for (int i = 0; i < 30; i++) {
		if (i == 0) rysuj = 0;
		temp = { 22,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	//pion belka 3
	for ( int i = 0; i < 30; i++) {
		if (i == 0) rysuj = 0;
		temp = { 78,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
	//pion belka 4
	for (int i = 0; i < 30; i++) {
		if (i == 0) rysuj = 0;
		temp = { 100,rysuj++ };
		SetConsoleCursorPosition(hConsole, temp);
		std::cout << pion_belka;
	}
}
void Fight::setHpBar()
{
	short pozycjaHPbaru = 7;
	COORD xy = { 12,  pozycjaHPbaru };  //recznie wpisane cordy hp baru gracza
	if (player.getPlayerHP() <= 0) {
		SetConsoleCursorPosition(hConsole, xy);  //czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci./start
		cout << "    ";
		SetConsoleCursorPosition(hConsole, xy);
		cout << "0";							//czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci/end

		pozycjaPokazywaniaAkcji = { 26, 25 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Przegrana!";

		pozycjaPokazywaniaAkcji = { 14, 31 };  //Powrot do pola wyboru zeby kursor nie wariowal
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	}
	else if(creature.getCreatureHp()<=0) {
		xy = { 89, 8 };    //recznie wpisane cordy hp baru enemy
		SetConsoleCursorPosition(hConsole, xy);   //czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.
		cout << "    ";
		SetConsoleCursorPosition(hConsole, xy);
		cout << "0";							//czyszcze pole hp i wstawiam 0 zamiast ujemnych wartosci.

		pozycjaPokazywaniaAkcji = { 32, 25 };  // Ustawiam kursor do wypisywania koncowego napisu
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		cout << "Wygrana!Zdobywasz " << 12 << " krysztalow";

		pozycjaPokazywaniaAkcji = { 14, 31 };  //Powrot do pola wyboru zeby kursor nie wariowal
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	}
	else {
		COORD xy = { 12,  pozycjaHPbaru };  //recznie wpisane cordy hp baru gracza
		SetConsoleCursorPosition(hConsole, xy);
		cout << "    ";
		SetConsoleCursorPosition(hConsole, xy);
		cout << player.getPlayerHP();

		xy = { 89, 8 };    //recznie wpisane cordy hp baru enemy
		SetConsoleCursorPosition(hConsole, xy);
		cout << "    ";
		SetConsoleCursorPosition(hConsole, xy);
		cout << creature.getCreatureHp();
	}

}
void Fight::showUIPlayerEnemy()
{
	
	short tempCreatureX = 80;
	short tempPlayerX = 3;
	short tempPlayerY = 2;
	short tempCreatureY = 3;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
	pozycjaPokazywaniaAkcji = { 0, 30 };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Rozpoczela sie walka pomiedzy " << player.getPlayerName() << " a " << creature.getCreatureName();
	pozycjaPokazywaniaAkcji = { 0, 31 };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Wybierz akcje: ";

	///////////////////////////////////
	// Enemy
	///////////////////////////////////

	pozycjaPokazywaniaAkcji = { 35,  2 };		
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << player.getPlayerName() << "      vs       " << creature.getCreatureName();

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Nazwa: " << creature.getCreatureName();
	tempCreatureY += 3;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Statystyki:";
	tempCreatureY+=2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY  };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Zycie: %5d", creature.getCreatureHp()); 
	tempCreatureY += 2;

	pozycjaPokazywaniaAkcji = { tempCreatureX, tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Atak: %5d", creature.getCreatureStrengh());
	tempCreatureY += 2;

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Obrona: %2d", creature.getCreatureDefence());
	tempCreatureY += 3;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_UMIEJETNOSCI);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Umiejetnosci:");
	tempCreatureY += 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_ENEMY);
	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout<<"Unik: "<<creature.getCreatureDodgeRate()<<"%";
	tempCreatureY += 2;

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Ogluszenie: " << creature.getMinotaurStunRate() << "%";
	tempCreatureY += 2;

	pozycjaPokazywaniaAkcji = { tempCreatureX,  tempCreatureY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Kradziez zycia: " << creature.creatureLifeStealRate() << "%";
	tempCreatureY += 2;

	////////////////////////////
	// player
	///////////////////////////
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Nazwa: " << player.getPlayerName();
	tempPlayerY = tempPlayerY + 3;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_STATYSTYK);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Statystyki:");
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Zycie:  %4d", player.getPlayerHP());
	tempPlayerY = tempPlayerY + 2;

	pozycjaPokazywaniaAkcji = { tempPlayerX, tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Energia: %3d", player.getPlayerEnergy());
	tempPlayerY = tempPlayerY + 2;

	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Atak: %5d", player.getPlayerStrengh());
	tempPlayerY = tempPlayerY + 2;

	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Obrona: %2d", player.getPlayerDefence());
	tempPlayerY=tempPlayerY+3;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_UMIEJETNOSCI);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Umiejetnosci: ");
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	printf("Regeneracja: +5E");
	tempPlayerY = tempPlayerY + 2;

	
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout <<"Unik: "  << player.getPlayerDodgeRate() << "%";
	tempPlayerY = tempPlayerY + 3;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_AKCJI);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "Akcje:  ";
	tempPlayerY = tempPlayerY + 2;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), STALA_KOLORU_TEXTU_PLAYERA);
	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "1)Atak(K:0)";
	tempPlayerY = tempPlayerY + 2;


	pozycjaPokazywaniaAkcji = { tempPlayerX,  tempPlayerY };
	SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
	cout << "2)Pchniecie(K:20)";
	tempPlayerY = tempPlayerY + 2;


}

void Fight::fightPlayerAttack()
{

	int option;		// wybor playera
	char ch;	    //w razie bledu
	clearChooseField(true);
	while (1) {
	wczytaj:
		
		pozycjaPokazywaniaAkcji = {14, 31 };  //KOD:101
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		if (scanf("%d", &option) != 1) {
			while (ch = getchar() != '\n');
			infoBrakWyboru(2);
			Sleep(100);
		}
		else if(option<=2) {

			  //inkrementacja rundy
			if (runda % 5 == 0 && runda != 0 && condition) {
				condition = false;
				clearCombat();
				rzad_Akcji = 8;//WARNING TU TEZ ZMIEN!
				pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };
                      
			}

				switch (option) 
					{
					case 1:
						if (creature.creatureDodge()) {
							pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
							rzad_Akcji++;
							cout << creature.getCreatureName() << " unika ataku!";
							clearChooseField(true);
							break;
						}
						creature.creatureHpDicrease(player.playerAttack());

						pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
						SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
						rzad_Akcji++;

						cout << player.getPlayerName();
						printf(" attakuje z sila :%-2d zostawiajac : %3d ",
							player.getPlayerTurnAttackValue() - creature.getCreatureDefence(), creature.getCreatureHp());
						clearChooseField(true);
						break;
					case 2:
						if (creature.creatureDodge()) {
							pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
							rzad_Akcji++;
							cout << creature.getCreatureName() << " unika ataku!";
							if (player.getPlayerEnergy() >= 50) {
								player.getDicreasePlayerEnergy(10);
								setEnergyBar();
							}
							clearChooseField(true);
							break;
						}
						if (player.getPlayerEnergy() >= 50) {
							player.getDicreasePlayerEnergy(20);
							creature.creatureHpDicrease( player.playerCrushingAttack() );
							pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };		//usawia cursor AKCJI
							SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
							rzad_Akcji++;
							cout << player.getPlayerName();
							printf(" attakuje z sila :%-2d zostawiajac : %3d ",
								player.getPlayerTurnAttackValue() - creature.getCreatureDefence(), creature.getCreatureHp());
							
							setEnergyBar();
							clearChooseField(true);
							break;
						}
						else {
								infoBrakWyboru(1);
								clearChooseField(false);
								goto wczytaj;
							}
					}
				roundLoop();
				condition = true;
				break;
		}
		else infoBrakWyboru(2);  //1 -brak energi 2-niewlasciwa akcja
	}
}
void Fight::fightCreatureAttack() {
	
	if (player.isDodge()) {
		pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		rzad_Akcji++;
		cout << "Uniknieto ataku";
		return;
	}
	else if (creature.getCreatureName() == "Minotaur" ) {
		if (creature.minotaurStun()) {
			pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
			SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
			rzad_Akcji++;
			rzad_Akcji++;

			player.playerDicreaseHP(creature.creatureAttack());
			cout << creature.getCreatureName();
			printf(" attakuje z sila :%-2d zostawiajac Ci : %3d ",
				creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
			pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
			SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
			rzad_Akcji++;
			cout << "Ogluszenie!";
		}
		pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		rzad_Akcji++;
		player.playerDicreaseHP(creature.creatureAttack());
		cout << creature.getCreatureName();
		printf(" attakuje z sila :%-2d zostawiajac Ci : %3d ",
			creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());

	}
	else if (creature.getCreatureName() == "Wampir" ) {
		if (creature.vampireBite() && creature.getCreatureHp()!=120) 
		{
			if (creature.getCreatureHp() < 120) {
				pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
				SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
				rzad_Akcji++;
				player.playerDicreaseHP(creature.creatureAttack());
				cout << creature.getCreatureName();
				printf(" attakuje z sila :%-2d zostawiajac Ci : %3d ",
					creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
				creature.lifeStealing(player.getPlayerDefence());
				pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
				SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
				rzad_Akcji++;
				cout << "Wampir kradnie zycie, leczac sie za " << creature.getCreatureTurnAttackValue()-player.getPlayerDefence();
			}
		}
		else {
			pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
			SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
			rzad_Akcji++;
			player.playerDicreaseHP(creature.creatureAttack());
			cout << creature.getCreatureName();
			printf(" attakuje z sila :%-2d zostawiajac Ci : %3d ",
				creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
		}


	}
	else if (creature.getCreatureName() == "Szkielet") {
		pozycjaPokazywaniaAkcji = { STALA, rzad_Akcji };					//usawia cursor
		SetConsoleCursorPosition(hConsole, pozycjaPokazywaniaAkcji);
		rzad_Akcji++;
		player.playerDicreaseHP(creature.creatureAttack());
		cout << creature.getCreatureName();
		printf(" attakuje z sila :%-2d zostawiajac Ci : %3d ",
			creature.getCreatureTurnAttackValue() - player.getPlayerDefence(), player.getPlayerHP());
	}


}

void Fight::setEnergyBar()
{
	COORD xy = { 12,  9 };
	SetConsoleCursorPosition(hConsole, xy);
	cout << "   ";
	SetConsoleCursorPosition(hConsole, xy);
	cout << player.getPlayerEnergy();
}
