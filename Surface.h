#pragma once
#include <vector>
#include <string>
class ColoredChar
{
private:
	const char c;
	int color;
public:
	ColoredChar(const char c, int color);
	int getColor() const;
	char getChar() const;
};

class Surface
{
private:
	std::vector< std::vector<ColoredChar*> > surface;
public:
	Surface(int width, int height);
	std::vector< std::vector<ColoredChar*> > getSurface() const;
	int printAt(const char *s, int color, int row, int column);
	int printAt(std::string s, int color, int row, int column);
	void print();
	int blit(Surface surface, int row, int column);
};


