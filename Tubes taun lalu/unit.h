#ifndef _UNIT_H
#define _UNIT_H

#include "point.h"
#include "mesinkata.h"

typedef struct{
	Kata type;
	Kata atktype;
	boolean canatk;
	int maxhealth;
	int currhealth;
	int atkdmg;
	int maxmove;
	int currmove;
	int heal;
	int cost;
	char simbol;
	int upkeepcost;
	int deff;
	int misschance;
	POINT pos;
} Unit;

typedef struct {
	char CC;
	int kepemilikan;
} CharUnit;

#define atktype(X) (X).atktype
#define canatk(X) (X).canatk
#define health(X) (X).health
#define atkdmg(X) (X).atkdmg
#define cost(X) (X).cost
#define heal(X) (X).heal
#define currmove(X) (X).currmove
#define position(X) (X).pos
#define pemilik(X) (X).kepemilikan
#define simbol(X) (X).simbol
#define CC(X) (X).CC

void PrintUnitRekrut(Unit U);

void PrintMove(Unit U);

void PrintUnit(Unit U);

boolean IsUnitSama(Unit a, Unit b);

void PrintNamaUnit(char X);

void PrintUnitAttack(Unit a, Unit b);


#endif
