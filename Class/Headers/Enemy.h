#include <cstdlib>
class Enemy
{
protected:
	
	int creatureHp,creatureDefence,creatureStrengh, creatureDodgeRate;
	
public:

	virtual  void creatureHpDicrease(int);
	virtual  int getCreatureHp() const;
	virtual  bool creatureDodge()const;
	virtual  int creatureAttack()const;
};


