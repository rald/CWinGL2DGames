#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "player.h"

typedef struct Enemy Enemy;

struct Enemy {
	double x,y;
	double radius;	
	double speed;
	double life;
};

Enemy *Enemy_New();

void Enemy_Draw(Enemy *enemy);

void Enemy_Update(Enemy *enemy,Player *player);

#endif
