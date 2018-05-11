#pragma once
#include <vector>
#include "Surface.h"
class Stage
{
public:
	virtual void show() = 0;
	virtual void command(char cmd) = 0;
};

