#include "Item.h"

Item::Item()
{
	this->Level = 1;
}

int Item::getLevel() const
{
	return this->Level;
}