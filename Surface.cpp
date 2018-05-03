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

Surface::Surface(int width, int height)
/*
Ustala rozmiar wektora
*/
{
	this->surface.resize(height, std::vector<ColoredChar*>(width, new ColoredChar('x', 55)));
}

int Surface::printAt(const char *s, int color, int row, int column)
/*
Dodaje ci¹g znaków do wektora na ustalon¹ pozycje
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
Dodaje ci¹g znaków do wektora na ustalon¹ pozycje
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

	for (int y = 0; y < this->getSurface().size(); y++)
	{
		for (int x = 0; x < this->getSurface()[0].size(); x++)
		{
			SetConsoleTextAttribute(hConsole, this->surface[y][x]->getColor());
			std::cout << this->surface[y][x]->getChar();
		}
		std::cout << std::endl;
	}

	SetConsoleTextAttribute(hConsole, 7);
}

int Surface::blit(Surface surface, int row, int column)
{
	std::cout << "---" << (this->surface.size() < (surface.getSurface().size() + row)) << "---" << std::endl;

	if (this->surface.size() < (surface.getSurface().size() + row) || this->surface[0].size() < (surface.getSurface()[0].size() + column))
		return 0;

	for (int y = 0; y < surface.getSurface().size(); y++)
	{
		for (int x = 0; x < surface.getSurface()[0].size(); x++)
		{
			this->surface[row + y][column + x] = surface.getSurface()[y][x];
		}
	}
	return 1;
}

std::vector< std::vector<ColoredChar*> > Surface::getSurface() const
{
	return this->surface;
}