#include <vector>
#include <Windows.h>
#include <iostream>
#include <string>
#include "Surface.h"
ColoredChar::ColoredChar(const char c, int color) : c(c), color(color)
{
}

int ColoredChar::getColor() const
/*
	Zwraca kolor znaku
*/
{
	return this->color;
}

char ColoredChar::getChar() const
/*
	Zwraca znak
*/
{
	return this->c;
}

/*
	TODO: Przy printAt nie sprawdzane jest czy nie przekroczono wymiaru wektora
*/

Surface::Surface(int width, int height)
/*
	Ustala rozmiar wektora
*/
{
	this->surface.resize(height, std::vector<ColoredChar*>(width, new ColoredChar(' ', 0)));
}

int Surface::printAt(const char s, int color, int row, int column)
/*
Dodaje znak do wektora na ustalona pozycje
*/
{
	if (this->surface[row].size() < column)
		return 0;

	this->surface[row][column] = new ColoredChar(s, color);

	return 1;
}

int Surface::printAt(const char *s, int color, int row, int column)
/*
	Dodaje ciag znakow do wektora na ustalona pozycje
*/
{
	if (this->surface[row].size() < (strlen(s) + column))
		return 0;

	for (int i = 0; i < strlen(s); i++)
	{
		this->surface[row][column + i] = new ColoredChar(s[i], color);
	}

	return 1;
}

int Surface::printAt(std::string s, int color, int row, int column)
/*
	Dodaje ciag znakow do wektora na ustalona pozycje
*/
{
	if (this->surface[row].size() < (s.size() + column))
		return 0;

	for (int i = 0; i < s.size(); i++)
	{
		this->surface[row][column + i] = new ColoredChar(s[i], color);
	}

	return 1;
}

void Surface::print()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int y = 0; y <this->surface.size(); y++)
	{
		for (int x = 0; x < this->surface[0].size(); x++)
		{
			SetConsoleTextAttribute(hConsole, this->surface[y][x]->getColor());
			std::cout << this->surface[y][x]->getChar();
		}
		std::cout << std::endl;
	}

	SetConsoleTextAttribute(hConsole, 7);
}

int Surface::blit(Surface surface, int row, int column)
/*
	Naklada innego Surface'a zaczynajac od podanego lewego gornego rogu
*/
{
	if (this->surface.size() < (this->surface.size() + row) || this->surface[0].size() < (this->surface[0].size() + column))
		return 0;

	for (int y = 0; y < this->surface.size(); y++)
	{
		for (int x = 0; x < this->surface[0].size(); x++)
		{
			this->surface[row + y][column + x] = this->surface[y][x];
		}
	}
	return 1;
}

void Surface::clear()
/*
	Do optymalizacji
*/
{
	for (int y = 0; y <this->surface.size(); y++)
	{
		for (int x = 0; x < this->surface[0].size(); x++)
		{
			this->surface[y][x] = new ColoredChar(' ', 0);
		}
	}
}

std::vector< std::vector<ColoredChar*> > Surface::get() const
{
	return this->surface;
}