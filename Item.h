#pragma once

class Item
{
protected:
	int Level;
public:
	Item();
	virtual void upgrade() = 0;
	int getLevel() const;
};