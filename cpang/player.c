#include "player.h"

Player *Player_New(glImage image,double x,double y,double speed) {
	Player *player=malloc(sizeof(Player));

	if(player) {
		player->image=image;	
		player->x=x;	
		player->y=y;
		player->speed=speed;
		player->dx=0;
		player->dy=0;
		player->g=GRAVITY;
		player->jumpHeight=JUMP_HEIGHT;
		player->canJump=false;
		player->canFire=true;
		player->state=PLAYER_STATE_JUMPING;
	}

	return player;
}

void Player_Delete(Player **player) {
	free(*player);
	*player=NULL;
}

void Player_UpdateIdle(Player *player) {
	player->dx=0;

	if(glfwGetKey('A')==GLFW_PRESS) {
		player->state=PLAYER_STATE_WALKING;
		player->dx=-player->speed;
		player->x+=player->dx;
	}

	if(glfwGetKey('D')==GLFW_PRESS) {
		player->state=PLAYER_STATE_WALKING;
		player->dx=player->speed;
		player->x+=player->dx;
	}

	if(glfwGetKey('L')==GLFW_PRESS) { 
		if(player->canJump) {
			player->state=PLAYER_STATE_JUMPING;
			player->dy=-player->jumpHeight;
			player->canJump=false;
		}
	}

	if(glfwGetKey('K')==GLFW_PRESS) {
		player->state=PLAYER_STATE_FIRING;
		player->canFire=false;
	}

	player->dy+=player->g;
	player->y+=player->dy;

	if(player->x<0) player->x=0;
	if(player->y<0) player->y=0;
	if(player->x>SCREEN_WIDTH-player->image.width) player->x=SCREEN_WIDTH-player->image.width;
	if(player->y>SCREEN_HEIGHT-player->image.height) {
		player->y=SCREEN_HEIGHT-player->image.height;
		player->dy=0;
		player->canJump=true;
	}
}

void Player_UpdateWalking(Player *player) {
	player->state=PLAYER_STATE_IDLE;

	player->dx=0;

	if(glfwGetKey('A')==GLFW_PRESS) {
		player->state=PLAYER_STATE_WALKING;
		player->dx=-player->speed;
		player->x+=player->dx;
	}

	if(glfwGetKey('D')==GLFW_PRESS) {
		player->state=PLAYER_STATE_WALKING;
		player->dx=player->speed;
		player->x+=player->dx;
	}

	if(glfwGetKey('L')==GLFW_PRESS) { 
		if(player->canJump) {
			player->state=PLAYER_STATE_JUMPING;
			player->dy=-player->jumpHeight;
			player->canJump=false;
		}
	}

	if(glfwGetKey('K')==GLFW_PRESS) {
		player->state=PLAYER_STATE_FIRING;
	}

	player->dy+=player->g;
	player->y+=player->dy;

	if(player->x<0) player->x=0;
	if(player->y<0) player->y=0;
	if(player->x>SCREEN_WIDTH-player->image.width) player->x=SCREEN_WIDTH-player->image.width;
	if(player->y>SCREEN_HEIGHT-player->image.height) {
		player->y=SCREEN_HEIGHT-player->image.height;
		player->dy=0;
		player->canJump=true;
	}
}

void Player_UpdateJumping(Player *player) {
	player->dx=0;

	if(glfwGetKey('A')==GLFW_PRESS) {
		player->dx=-player->speed;
		player->x+=player->dx;
	}

	if(glfwGetKey('D')==GLFW_PRESS) {
		player->dx=player->speed;
		player->x+=player->dx;
	}

	player->dy+=player->g;
	player->y+=player->dy;

	if(player->x<0) player->x=0;
	if(player->y<0) player->y=0;
	if(player->x>SCREEN_WIDTH-player->image.width) player->x=SCREEN_WIDTH-player->image.width;
	if(player->y>SCREEN_HEIGHT-player->image.height) {
		player->state=PLAYER_STATE_IDLE;
		player->y=SCREEN_HEIGHT-player->image.height;
		player->dy=0;
		player->canJump=true;
	}

}

void Player_UpdateFiring(Player *player) {
	player->state=PLAYER_STATE_IDLE;
}

void Player_Draw(Player *player) {
	glSprite(player->x,player->y,GL2D_FLIP_NONE,&player->image);
}

void Player_Update(Player *player) {
	switch(player->state) {
		case PLAYER_STATE_IDLE: Player_UpdateIdle(player); break;
		case PLAYER_STATE_WALKING: Player_UpdateWalking(player); break;
		case PLAYER_STATE_JUMPING: Player_UpdateJumping(player); break;
		case PLAYER_STATE_FIRING: Player_UpdateFiring(player); break;
	}
}
