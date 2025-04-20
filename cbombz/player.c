#include "player.h"

Player *Player_New(double x,double y) {
	Player *player=malloc(sizeof(Player));
	
	if(player) {
		player->x=x;
		player->y=y;
		player->radius=16.0;
		player->speed=4.0;
		player->life=1;
	}

	return player;
}

void Player_Draw(Player *player) {
	double radius=player->life*player->radius;
	glEllipseFilled(player->x,player->y,radius,radius,0,GL2D_RGBA(0,255,0,255));
	glEllipse(player->x,player->y,player->radius,player->radius,0,GL2D_RGBA(255,255,255,255));
}

void Player_Update(Player *player) {
	if(player->life<=0) player->life=0;

	if(player->x<player->radius) player->x=player->radius;
	if(player->y<player->radius) player->y=player->radius;
	if(player->x>SCREEN_WIDTH-player->radius-1) player->x=SCREEN_WIDTH-player->radius-1;
	if(player->y>SCREEN_HEIGHT-player->radius-1) player->y=SCREEN_HEIGHT-player->radius-1;
}

void Player_HandleEvents(Player *player,Bomb *bombs[],int *numBombs) {
	static bool hold=false;

	if(glfwGetKey('W')) player->y-=player->speed;
	if(glfwGetKey('S')) player->y+=player->speed;
	if(glfwGetKey('A')) player->x-=player->speed;
	if(glfwGetKey('D')) player->x+=player->speed;

	if(glfwGetKey('L')) {
		if(!hold) {
			hold=true;
			if((*numBombs)<BOMBS_MAX) {
				bombs[(*numBombs)++]=Bomb_New(player->x,player->y);
			}
		}
	} else {
		hold=false;
	}
}
