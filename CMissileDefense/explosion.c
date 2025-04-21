#include "explosion.h"

Explosion *Explosion_New(double x,double y,double dstRadius,double speed,GLuint color) {
	Explosion *explosion=malloc(sizeof(*explosion));
	if(explosion) {
		explosion->x=x;
		explosion->y=y;
		explosion->srcRadius=0;
		explosion->dstRadius=dstRadius;
		explosion->radius=explosion->srcRadius;
		explosion->direction=1;
		explosion->speed=speed;
		explosion->color=color;
	}
	return explosion;
}

void Explosion_Draw(Explosion *explosion) {
	glEllipse(explosion->x,explosion->y,explosion->radius,explosion->radius,0,explosion->color);
}

void Explosion_Update(Explosion *explosion) {
	explosion->radius+=explosion->speed*explosion->direction;
	if(explosion->direction>0 && abs(explosion->radius-explosion->dstRadius)<1) {
		explosion->direction=-1;
	}
}

void Explosion_Delete(void *explosion) {
	free((Explosion*)explosion);
	explosion=NULL;
}
