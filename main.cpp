#include <stdio.h>
#include <conio.h>
#include "Skeleton.h"
#include <Windows.h>
#include "Minotaur.h"
#include "Player.h"
#include "Fight.h"
#include <iostream>
using namespace std;
int main() {
	Player player = Player();
	player.setPlayerName("Etanolix");
	Enemy enemy = Minotaur();
	if (true) {
		Fight fight = Fight(player, 1);
		fight.fightStart();
	}
	Sleep(2000);
	//fight.startFight();  
	/*getchar();
	getchar();

	if(true)
		Fight fight = Fight(player, 3);*/
	getchar();
	getchar();
	return 0;
}
