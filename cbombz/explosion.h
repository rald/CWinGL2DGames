#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "common.h"

typedef struct Explosion Explosion;

struct Explosion {
	double x,y;
	double radius;	
	double minRadius;	
	double maxRadius;	
	double velRadius;	
};

Explosion *Explosion_New(double x,double y);

void Explosion_Draw(Explosion *explosion);

void Explosion_Update(Explosion *explosion);

#endif
