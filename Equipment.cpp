#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Equipment.h"

using namespace std;

Equipment::Equipment()
{
	this->weapon = new Weapon();
	this->shield = new Shield();
	this->armor = new Armor();
	this->boots = new Boots();

	this->crystals = 0;
}

int Equipment::getDefense() const
{
	return this->shield->getDefenseValue() + this->armor->getDefenseValue() + this->boots->getDefenseValue();
}
int Equipment::getEnergy() const
{
	return this->shield->getAddEnergyValue();
}
int Equipment::getAttack() const
{
	return this->weapon->getAttackValue();
}
int Equipment::getDodgeRate() const
{
	return this->boots->getAddDodgeRateValue();
}
int Equipment::getHp() const
{
	return this->armor->getAddHpValue();
}
int Equipment::getCrystals() const
{
	return crystals;
}
void Equipment::addCrystals(int x)
{
	this->crystals += x;
}

void Equipment::subCrystals(int x)
{
	this->crystals -= x;
}

void Equipment::show()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos{25, 5};

	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 12);
	cout << "Kryszta³y: " << this->getCrystals();

	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Miecz____________ Koszt ulepszenia: " << this->weapon->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Atak:     " <<  weapon->getAttackValue();
	
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Zbroja___________ Koszt ulepszenia: " << this->armor->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos); 
	cout << "Obrona:   " << armor->getDefenseValue();
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Zdrowie:  " << armor->getAddHpValue();
	
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Tarcza___________ Koszt ulepszenia: " << this->shield->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Obrona:   " << shield->getDefenseValue();
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Energia:  " << shield->getAddEnergyValue();
	
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Buty_____________ Koszt ulepszenia: " << this->boots->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Obrona:   " << boots->getDefenseValue();
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Unik:     " << boots->getAddDodgeRateValue();

	SetConsoleTextAttribute(hConsole, 15);
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "z: Ulepsz miecz";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "x: Ulepsz zbrojê";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "c: Ulepsz tarczê";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "v: Ulepsz buty";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "m: Mapa";
}

void Equipment::command(char cmd)
{
	switch (cmd)
	{
	case 'z':
		if ((this->getCrystals() - this->weapon->getLevel() * 20) >= 0)
		{
			this->subCrystals(this->weapon->getLevel() * 20);
			this->weapon->upgrade();
		}
		break;
	case 'x':
		if ((this->getCrystals() - this->armor->getLevel() * 20) >= 0)
		{
			this->subCrystals(this->armor->getLevel() * 20);
			this->armor->upgrade();
		}
		break;
	case 'c':
		if ((this->getCrystals() - this->shield->getLevel() * 20) >= 0)
		{
			this->subCrystals(this->shield->getLevel() * 20);
			this->shield->upgrade();
		}
		break;
	case 'v':
		if ((this->getCrystals() - this->boots->getLevel() * 20) >= 0)
		{
			this->subCrystals(this->boots->getLevel() * 20);
			this->boots->upgrade();
		}
		break;
	}
	system("cls");
}

Equipment::~Equipment()
{
	delete this->weapon;
	delete this->shield;
	delete this->armor;
	delete this->boots;
}