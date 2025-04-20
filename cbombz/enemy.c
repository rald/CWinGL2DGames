#include "enemy.h"



double sgn(double x) {
	return x<0?-1:x>0?1:0;
}



Enemy *Enemy_New() {
	Enemy *enemy=malloc(sizeof(Enemy));
	
	if(enemy) {
		enemy->x=0;
		enemy->y=0;
		enemy->radius=16.0;
		enemy->speed=0.5;
		enemy->life=1;
	}

	return enemy;
}

void Enemy_Draw(Enemy *enemy) {
	double radius=enemy->life*enemy->radius;
	glEllipseFilled(enemy->x,enemy->y,radius,radius,0,GL2D_RGBA(255,0,0,255));
	glEllipse(enemy->x,enemy->y,enemy->radius,enemy->radius,0,GL2D_RGBA(255,255,255,255));
}

void Enemy_Update(Enemy *enemy,Player *player) {


	double angle=atan2(player->y-enemy->y,player->x-enemy->x);

	enemy->x+=cos(angle)*enemy->speed;
	enemy->y+=sin(angle)*enemy->speed;

	if(enemy->life<=0) enemy->life=0;

}

