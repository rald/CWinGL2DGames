#include "bomb.h"

Bomb *Bomb_New(double x,double y) {
	Bomb *bomb=malloc(sizeof(Bomb));
	
	if(bomb) {
		bomb->x=x;
		bomb->y=y;
		bomb->minRadius=12.0;
		bomb->maxRadius=16.0;
		bomb->radius=bomb->maxRadius;
		bomb->velRadius=1.0;
		bomb->maxTime=100;
		bomb->time=bomb->maxTime;
	}

	return bomb;
}

void Bomb_Draw(Bomb *bomb) {
	glEllipseFilled(bomb->x,bomb->y,bomb->radius,bomb->radius,0,GL2D_RGBA(0,0,0,255));
	glEllipse(bomb->x,bomb->y,bomb->radius,bomb->radius,0,GL2D_RGBA(255,255,255,255));
}

void Bomb_Update(Bomb *bomb) {

	bomb->radius+=bomb->velRadius;

	if(bomb->radius<bomb->minRadius) bomb->velRadius=abs(bomb->velRadius);
	if(bomb->radius>bomb->maxRadius) bomb->velRadius=-abs(bomb->velRadius);

	if(bomb->x<bomb->radius) bomb->x=bomb->radius;
	if(bomb->y<bomb->radius) bomb->y=bomb->radius;
	if(bomb->x>SCREEN_WIDTH-bomb->radius-1) bomb->x=SCREEN_WIDTH-bomb->radius-1;
	if(bomb->y>SCREEN_HEIGHT-bomb->radius-1) bomb->y=SCREEN_HEIGHT-bomb->radius-1;

	bomb->time--;
	if(bomb->time<=0) {
		bomb->time=0;
	}
	
}
