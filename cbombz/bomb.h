#ifndef BOMB_H
#define BOMB_H

#include "common.h"

typedef struct Bomb Bomb;

struct Bomb {
	double x,y;
	double radius;	
	double minRadius;	
	double maxRadius;	
	double velRadius;	
	double time;
	double maxTime;
};

Bomb *Bomb_New(double x,double y);

void Bomb_Draw(Bomb *bomb);

void Bomb_Update(Bomb *bomb);

#endif
