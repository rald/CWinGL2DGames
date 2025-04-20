#ifndef BUBBLE_H
#define BUBBLE_H

#include "common.h"

typedef struct Bubble Bubble;

struct Bubble{
	glImage *images;
	double x,y;
	double dx,dy;
	double vx,vy;
	double g;
	int size;
};


Bubble *Bubble_New(
		glImage *images,
		double x,double y,
		int size,
		double vx,double vy);

void Bubble_Delete(Bubble **bubble);
void Bubble_Draw(Bubble *bubble);
void Bubble_Update(Bubble *bubble);

#endif
