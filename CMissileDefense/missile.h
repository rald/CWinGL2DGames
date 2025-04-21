#ifndef MISSILE_H
#define MISSILE_H

#include <stdlib.h>
#include <math.h>

#include "GL/gl2d.h"

typedef struct Missile Missile;
struct Missile {
	double x,y;
	double srcX,srcY;
	double dstX,dstY;
	double heading;
	double speed;
	GLuint color;
};

Missile *Missile_New(double srcX,double srcY,double dstX,double dstY,double speed,GLuint color);
void Missile_Draw(Missile *missile);
void Missile_Update(Missile *missile);
void Missile_Delete(void *missile);

#endif
