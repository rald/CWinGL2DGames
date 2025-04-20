#ifndef PLAYER_H
#define PLAYER_H

#include "common.h"
#include "bomb.h"

typedef struct Player Player;

struct Player {
	double x,y;
	double radius;	
	double speed;
	double life;
};

Player *Player_New(double x,double y);

void Player_Draw(Player *player);

void Player_Update(Player *player);

void Player_HandleEvents(Player *player,Bomb *bombs[],int *numBombs);

#endif
