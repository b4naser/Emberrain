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
	cout << "Crystals: " << this->getCrystals();

	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Weapon__________ Upgrade cost: " << this->weapon->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Attack:     " <<  weapon->getAttackValue();
	
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Armor___________ Upgrade cost: " << this->armor->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos); 
	cout << "Defense:    " << armor->getDefenseValue();
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Health:     " << armor->getAddHpValue();
	
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Shield__________ Upgrade cost: " << this->shield->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Defense:    " << shield->getDefenseValue();
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Energy:     " << shield->getAddEnergyValue();
	
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	SetConsoleTextAttribute(hConsole, 3);
	cout << "Boots___________ Upgrade cost: " << this->boots->getLevel() * 20;
	SetConsoleTextAttribute(hConsole, 7);
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Defense:    " << boots->getDefenseValue();
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "Dodge rate: " << boots->getAddDodgeRateValue();

	SetConsoleTextAttribute(hConsole, 15);
	cursorPos.Y += 2;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "z: Upgrade sword";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "x: Upgrade armor";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "c: Upgrade shield";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "v: Upgrade boots";
	cursorPos.Y += 1;
	SetConsoleCursorPosition(hConsole, cursorPos);
	cout << "m: View map";
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