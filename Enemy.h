#pragma once
#include <string>
#include <cstdlib>
#include <time.h>
#include <random>
class Enemy
{
protected:
	int creatureHp,         //zdrowie przeciwnika
		creatureDefence,    //obrona przeciwnika
		creatureStrength;   //si�a przeciwnika
	std::string creatureName;   //nazwa przeciwnika
	int creatureTurnAttackValue,    //turowa warto�� ataku gracza
		creatureLifeSteal,          //ilo�� �ycia kt�r� przeciwnik zada� graczowi, a nast�pnie uleczy� si�
		creatureLifeStealRate,      //szansa na kradzie� �ycia
		creatureStunRate,           //szansa na og�uszenie
		creatureDodgeRate;         //szansa na unik
public:
	virtual  void creatureHpDecrease(int); //przyjmuje warto�� ataku zadan� przez gracza i zmniejsza zdrowi� przeciwnika o jego warto��
	virtual  bool creatureDodge()const;     //sprawdzenie czy przeciwnik unikn�� ataku
	virtual  int creatureAttack();          //atak przeciwnika
	virtual bool creatureTryToStealLife();  //sprawdzenie czy przeciwnik u�y� umiej�tno�ci kradzie�y �ycia
	virtual void creatureStealLife(int);    //przeciwnik kradnie �ycie
	virtual bool creatureTryStun();     //sprawdzenie czy przeciwnik og�uszy� gracza

	virtual int getCreatureStunRate()const;     //zwraca zasi�g og�uszenia gracza przez przeciwnika
	virtual int getCreatureLifeStealRate()const;    //zwraca warto�� kradzie�y �ycia gracza przez przeciwnika
	virtual int getCreatureDodgeRate() const;       //zwraca warto�� uniku przeciwnika
	virtual int getCreatureStrength() const;        //zwraca si�� przeciwnika
	virtual int getCreatureDefence() const;         //zwraca obron� przeciwnika
	virtual  int getCreatureHp() const;             //zwraca zdrowie przeciwnika
	virtual std::string getCreatureName()const;     //zwraca nazw� przeciwnika
	virtual int getCreatureTurnAttackValue()const;  //zwraca turow� warto�� ataku przeciwnika
public:
	Enemy();
};