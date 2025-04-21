#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <stdlib.h>

#include "gl2d.h"

typedef struct Explosion Explosion;
struct Explosion {
	double x,y,radius,srcRadius,dstRadius;
	double direction;
	double speed;
	GLuint color;
};

Explosion *Explosion_New(double x,double y,double dstRadius,double speed,GLuint color);
void Explosion_Draw(Explosion *explosion);
void Explosion_Update(Explosion *explosion);
void Explosion_Delete(void *explosion);

#endif
