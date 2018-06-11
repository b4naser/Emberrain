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
		creatureStrength;   //si³a przeciwnika
	std::string creatureName;   //nazwa przeciwnika
	int creatureTurnAttackValue,    //turowa wartoœæ ataku gracza
		creatureLifeSteal,          //iloœæ ¿ycia któr¹ przeciwnik zada³ graczowi, a nastêpnie uleczy³ siê
		creatureLifeStealRate,      //szansa na kradzie¿ ¿ycia
		creatureStunRate,           //szansa na og³uszenie
		creatureDodgeRate;         //szansa na unik
public:
	virtual  void creatureHpDecrease(int); //przyjmuje wartoœæ ataku zadan¹ przez gracza i zmniejsza zdrowiê przeciwnika o jego wartoœæ
	virtual  bool creatureDodge()const;     //sprawdzenie czy przeciwnik unikn¹³ ataku
	virtual  int creatureAttack();          //atak przeciwnika
	virtual bool creatureTryToStealLife();  //sprawdzenie czy przeciwnik u¿y³ umiejêtnoœci kradzie¿y ¿ycia
	virtual void creatureStealLife(int);    //przeciwnik kradnie ¿ycie
	virtual bool creatureTryStun();     //sprawdzenie czy przeciwnik og³uszy³ gracza

	virtual int getCreatureStunRate()const;     //zwraca zasiêg og³uszenia gracza przez przeciwnika
	virtual int getCreatureLifeStealRate()const;    //zwraca wartoœæ kradzie¿y ¿ycia gracza przez przeciwnika
	virtual int getCreatureDodgeRate() const;       //zwraca wartoœæ uniku przeciwnika
	virtual int getCreatureStrength() const;        //zwraca si³ê przeciwnika
	virtual int getCreatureDefence() const;         //zwraca obronê przeciwnika
	virtual  int getCreatureHp() const;             //zwraca zdrowie przeciwnika
	virtual std::string getCreatureName()const;     //zwraca nazwê przeciwnika
	virtual int getCreatureTurnAttackValue()const;  //zwraca turow¹ wartoœæ ataku przeciwnika
public:
	Enemy();
};