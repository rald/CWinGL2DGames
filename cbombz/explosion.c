#include "explosion.h"

Explosion *Explosion_New(double x,double y) {
	Explosion *explosion=malloc(sizeof(Explosion));
	
	if(explosion) {
		explosion->x=x;
		explosion->y=y;
		explosion->radius=1.0;
		explosion->maxRadius=64.0;
		explosion->velRadius=4.0;
	}

	return explosion;
}

void Explosion_Draw(Explosion *explosion) {
	glEllipse(explosion->x,explosion->y,explosion->radius,explosion->radius,0,GL2D_RGBA(255,255,255,255));
}

void Explosion_Update(Explosion *explosion) {

	explosion->radius+=explosion->velRadius;

	if(explosion->radius<=0) explosion->radius=0;
	if(explosion->radius>explosion->maxRadius) explosion->velRadius=-abs(explosion->velRadius);
}
