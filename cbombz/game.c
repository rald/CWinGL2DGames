#define _GNU_SOURCE
#include "common.h"
#include "player.h"
#include "enemy.h"
#include "bomb.h"
#include "explosion.h"

double dist(double x0,double y0,double x1,double y1) {
	return sqrt(pow(x1-x0,2)+pow(y1-y0,2));
}

int main(int argc, char *argv[]) {

	bool quit = false;

	Enemy *enemies[ENEMIES_MAX];
	int numEnemies=0; 

	int enemySpawnDelay=100;
	int enemySpawnCounter=0;

	Bomb *bombs[BOMBS_MAX];
	int numBombs=0; 

	Explosion *explosions[EXPLOSIONS_MAX];
	int numExplosions=0; 

	int score=0;

	bool gameover=false;

	int i,j;



	srand(time(NULL));

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);
	glfwSetWindowTitle(GAME_TITLE);
	glfwSwapInterval(1);

	Player *player=Player_New(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);

	while(!quit) {



		if(!gameover) Player_HandleEvents(player,bombs,&numBombs);



		for(i=0;i<numBombs;i++) {
			Bomb_Update(bombs[i]);
		}

		if(!gameover) Player_Update(player);

		for(i=0;i<numEnemies;i++) {
			Enemy_Update(enemies[i],player);
		}

		for(i=0;i<numExplosions;i++) {
			Explosion_Update(explosions[i]);
		}


		for(i=0;i<numEnemies;i++) {
			if(dist(player->x,player->y,enemies[i]->x,enemies[i]->y)<=player->radius+enemies[i]->radius) {
				player->life-=0.01;
			}
		}

		for(i=0;i<numExplosions;i++) {
			if(dist(player->x,player->y,explosions[i]->x,explosions[i]->y)<=player->radius+explosions[i]->radius) {
				player->life-=0.01;
			}
		}


		if(player->life<=0) gameover=true;
	
		for(i=numEnemies-1;i>=0;i--) {

			for(j=0;j<numExplosions;j++) {
				if(dist(enemies[i]->x,enemies[i]->y,explosions[j]->x,explosions[j]->y)<=enemies[i]->radius+explosions[j]->radius) {
					enemies[i]->life-=0.05;
				}
			}

			if(enemies[i]->life<=0) {
 				for(j=i;j<numEnemies-1;j++) {
					enemies[j]=enemies[j+1];
				}
				numEnemies--;
				score++;
 			}
	 	}


		for(i=numBombs-1;i>=0;i--) {

			for(j=0;j<numExplosions;j++) {
				if(dist(bombs[i]->x,bombs[i]->y,explosions[j]->x,explosions[j]->y)<=bombs[i]->radius+explosions[j]->radius) {
					bombs[i]->time=0;
					break;
				}
			}

			if(bombs[i]->time<=0) {

				explosions[numExplosions++]=Explosion_New(bombs[i]->x,bombs[i]->y);

				for(j=i;j<numBombs-1;j++) {
					bombs[j]=bombs[j+1];
				}
				numBombs--;
			}
		}

		for(i=numExplosions-1;i>=0;i--) {
			if(explosions[i]->radius<=0) {
				for(j=i;j<numExplosions-1;j++) {
					explosions[j]=explosions[j+1];
				}
				numExplosions--;
 			}
		}


		glClearScreen();


		for(i=0;i<numBombs;i++) {
			Bomb_Draw(bombs[i]);
		}

		if(!gameover) Player_Draw(player);

		for(i=0;i<numEnemies;i++) {
			Enemy_Draw(enemies[i]);
		}

		for(i=0;i<numExplosions;i++) {
			Explosion_Draw(explosions[i]);
		}


		char scoreStr[256];

		sprintf(scoreStr,"Score: %d",score);

		glPrint(10,10,scoreStr,GL2D_RGBA(0,255,0,255));

		if(gameover) {
			glPrint(SCREEN_WIDTH-10-10*9,10,"GAME OVER",GL2D_RGBA(0,255,0,255));
		}

		if(!gameover && numEnemies<ENEMIES_MAX) {
			enemySpawnCounter++;
			if(enemySpawnCounter>=enemySpawnDelay) {
				enemySpawnCounter=0;

				enemies[numEnemies]=Enemy_New();

				switch(rand()%4) {
					case 0: 
						enemies[numEnemies]->x=rand()%SCREEN_WIDTH;
						enemies[numEnemies]->y=-enemies[numEnemies]->radius*2;
					break;
					case 1: 
						enemies[numEnemies]->x=rand()%SCREEN_WIDTH;
						enemies[numEnemies]->y=SCREEN_HEIGHT+enemies[numEnemies]->radius*2;
					break;
					case 2: 
						enemies[numEnemies]->x=-enemies[numEnemies]->radius*2;
						enemies[numEnemies]->y=rand()%SCREEN_HEIGHT;
					break;
					case 3: 
						enemies[numEnemies]->x=SCREEN_WIDTH+enemies[numEnemies]->radius*2;
						enemies[numEnemies]->y=rand()%SCREEN_HEIGHT;
					break;
				}

				numEnemies++;

			}
		}



		float TimeStart=glfwGetTime();
		while((glfwGetTime()-TimeStart)<(1.0/100.0)){};
	
		glfwSwapBuffers();
	
		quit=glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}
	
	glfwTerminate();

	return 0;
}

