#include "missile.h"

Missile *Missile_New(double srcX,double srcY,double dstX,double dstY,double speed,GLuint color) {
	Missile *missile=malloc(sizeof(*missile));
	if(missile) {
		missile->x=srcX;
		missile->y=srcY;
		missile->srcX=srcX;
		missile->srcY=srcY;
		missile->dstX=dstX;
		missile->dstY=dstY;
		missile->color=color;
		missile->speed=speed;
	}
	return missile;
}

void Missile_Update(Missile *missile) {
	missile->heading=atan2(missile->dstY-missile->y,missile->dstX-missile->x);
	missile->x+=missile->speed*cos(missile->heading);
	missile->y+=missile->speed*sin(missile->heading);
}

void Missile_Draw(Missile *missile) {
	glLine(missile->srcX,missile->srcY,missile->x,missile->y,missile->color);
}

void Missile_Delete(void *missile) {
	free((Missile*)missile);
	missile=NULL;
}
