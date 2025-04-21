#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#include "GL/glfw.h"
#include "GL/gl2d.h"

#include "utils.h"
#include "list.h"
#include "turret.h"
#include "missile.h"
#include "explosion.h"
#include "building.h"

#define GAME_TITLE "CMissileDefense"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define FIXED_TIME_STEP (1.0/60.0)

int __dso_handle;

bool gameover=false;

bool quit=false;
int mouseX,mouseY;
int mouseButton;
bool mouseButtonLeftPressed=false;

Turret *playerTurret=NULL;
ListNode *playerMissiles=NULL;
ListNode *enemyMissiles=NULL;
ListNode *explosions=NULL;
ListNode *buildings=NULL;

double damage=0.1;

double playerMissileSpeed=4;
double playerMissileExplosionRadius=50;
double playerMissileExplosionSpeed=1;

double enemyMissileSpeed=0.5;
double enemyMissileExplosionRadius=50;
double enemyMissileExplosionSpeed=1;

int enemyMissileSpawnCounter=0;
int enemyMissileSpawnCounterMax=50;

double turretRadius=10;
double turretHeading=0;
double turretLifeMax=100.0;

int numBuildings=0;
double buildingRadius=10;
double buildingLifeMax=100.0;

int score=0;

double getDeltaTime(double *fps,double timerInSeconds);
void update();
void draw();



double getDeltaTime(double *fps,double timerInSeconds) {
	static double framesPerSecond=0.0;
	static double previousTime=0.0;
	static double oldTime=0.0;
	double currentTime=timerInSeconds;
	double elapsedTime=currentTime-oldTime;

	oldTime=currentTime;
	framesPerSecond+=1;

	if((currentTime-previousTime)>1.0) {
	  previousTime=currentTime;
		*fps=framesPerSecond;
	   framesPerSecond=0;
	}

	return elapsedTime;
}



void update() {

  glfwGetMousePos(&mouseX,&mouseY);

	if(!gameover) {
		ListNode *explosionIter;
		Turret_Update(playerTurret);
		for(explosionIter=explosions;explosionIter;explosionIter=explosionIter->next) {
			Explosion *explosion=explosionIter->data;
			if(distance(playerTurret->x1,playerTurret->y1,explosion->x,explosion->y)<=playerTurret->radius+explosion->radius) {
				if(playerTurret->life>0) {
					playerTurret->life-=damage;
				} else {
					playerTurret->life=0;
					gameover=true;
				}
			}
		}

		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
	    if(!mouseButtonLeftPressed) {
	      mouseButtonLeftPressed=true;
	      List_Push(&playerMissiles,Missile_New(playerTurret->x2,playerTurret->y2,mouseX,mouseY,playerMissileSpeed,GL2D_RGBA(0x00,0xFF,0x00,0xFF)),Missile_Delete);
	    }
	  } else if(mouseButtonLeftPressed) {
	    mouseButtonLeftPressed=false;
	  }
	}

	if(buildings || !gameover) {
		enemyMissileSpawnCounter++;
		if(enemyMissileSpawnCounter>=enemyMissileSpawnCounterMax) {
			int side=rand()%4;
			double x,y;
			enemyMissileSpawnCounter=0;
			switch(side) {
				case 0: x=SCREEN_WIDTH; y=rand()%SCREEN_HEIGHT; break;
				case 1: x=rand()%SCREEN_WIDTH; y=0; break;
				case 2: x=0; y=rand()%SCREEN_HEIGHT; break;
				case 3: x=rand()%SCREEN_WIDTH; y=SCREEN_HEIGHT; break;
			}

			int target=rand()%2;
			if(target==0 && !gameover) {
				List_Push(&enemyMissiles,Missile_New(x,y,playerTurret->x1,playerTurret->y1,enemyMissileSpeed,GL2D_RGBA(0x00,0xFF,0x00,0xFF)),Missile_Delete);
			} else {
				int n=0;
				ListNode *buildingIter=buildings;
				Building *selectedBuilding=NULL;
				while(buildingIter) {
					if((rand()/(double)RAND_MAX)<=(1.0/n)) selectedBuilding=buildingIter->data;
					buildingIter=buildingIter->next;
					n++;
				}
				if(selectedBuilding) {
					List_Push(&enemyMissiles,Missile_New(x,y,selectedBuilding->x,selectedBuilding->y,enemyMissileSpeed,GL2D_RGBA(0x00,0xFF,0x00,0xFF)),Missile_Delete);
				}
			}
		}
	}

  if(enemyMissiles) {
    ListNode *enemyMissileIter;
    ListNode *explosionIter;
		ListNode *buildingIter;
		for(enemyMissileIter=enemyMissiles;enemyMissileIter;enemyMissileIter=enemyMissileIter->next) {
      Missile *enemyMissile=enemyMissileIter->data;
			Missile_Update(enemyMissile);
      if( distance(enemyMissile->x,enemyMissile->y,enemyMissile->dstX,enemyMissile->dstY)<1 ||
          distance(enemyMissile->x,enemyMissile->y,playerTurret->x1,playerTurret->y1)<playerTurret->radius) {
        enemyMissileIter->active=false;
      }
  		for(explosionIter=explosions;explosionIter;explosionIter=explosionIter->next) {
        Explosion *explosion=explosionIter->data;
        if(distance(enemyMissile->x,enemyMissile->y,explosion->x,explosion->y)<explosion->radius) {
          enemyMissileIter->active=false;
					score++;
        }
  		}
			for(buildingIter=buildings;buildingIter;buildingIter=buildingIter->next) {
        Building *building=buildingIter->data;
        if(distance(enemyMissile->x,enemyMissile->y,building->x,building->y)<building->radius) {
          enemyMissileIter->active=false;
        }
  		}
			if(!enemyMissileIter->active) {
				List_Push(&explosions,Explosion_New(enemyMissile->x,enemyMissile->y,enemyMissileExplosionRadius,enemyMissileExplosionSpeed,GL2D_RGBA(0x00,0xFF,0x00,0xFF)),Explosion_Delete);
			}
		}
		List_RemoveInactive(&enemyMissiles);
  }

  if(playerMissiles) {
		ListNode *playerMissileIter;
    ListNode *explosionIter;
		for(playerMissileIter=playerMissiles;playerMissileIter;playerMissileIter=playerMissileIter->next) {
      Missile *missile=playerMissileIter->data;
			Missile_Update(missile);
      if(distance(missile->x,missile->y,missile->dstX,missile->dstY)< missile->speed) {
        playerMissileIter->active=false;
      }
      for(explosionIter=explosions;explosionIter;explosionIter=explosionIter->next) {
        Explosion *explosion=explosionIter->data;
        if(distance(missile->x,missile->y,explosion->x,explosion->y)<explosion->radius) {
          playerMissileIter->active=false;
        }
  		}
			if(!playerMissileIter->active) {
				List_Push(&explosions,Explosion_New(missile->x,missile->y,playerMissileExplosionRadius,playerMissileExplosionSpeed,GL2D_RGBA(0x00,0xFF,0x00,0xFF)),Explosion_Delete);
			}
		}
		List_RemoveInactive(&playerMissiles);
	}

  if(explosions) {
		ListNode *explosionIter;
		for(explosionIter=explosions;explosionIter;explosionIter=explosionIter->next) {
      Explosion *explosion=explosionIter->data;
			Explosion_Update(explosion);
      if(explosion->direction<0 && abs(explosion->radius-explosion->srcRadius)<1) {
    		explosionIter->active=false;
    	}
		}
		List_RemoveInactive(&explosions);
	}

	if(buildings) {
		ListNode *buildingIter;
		ListNode *explosionIter;
		for(buildingIter=buildings;buildingIter;buildingIter=buildingIter->next) {
      Building *building=buildingIter->data;
			for(explosionIter=explosions;explosionIter;explosionIter=explosionIter->next) {
        Explosion *explosion=explosionIter->data;
				if(distance(building->x,building->y,explosion->x,explosion->y)<building->radius+explosion->radius) {
					if(building->life>0) {
						building->life-=damage;
					} else {
						building->life=0;
						buildingIter->active=false;
						numBuildings--;
					}
				}
  		}
		}
		List_RemoveInactive(&buildings);
	}

}



void draw() {
  ListNode *enemyMissileIter;
  ListNode *playerMissileIter;
  ListNode *explosionIter;
	ListNode *buildingIter;

  glBegin2D(SCREEN_WIDTH,SCREEN_HEIGHT);

		if(!gameover) {
			Turret_Draw(playerTurret);
		}

		for(buildingIter=buildings;buildingIter;buildingIter=buildingIter->next) {
      Building_Draw(buildingIter->data);
    }

		for(enemyMissileIter=enemyMissiles;enemyMissileIter;enemyMissileIter=enemyMissileIter->next) {
      Missile_Draw(enemyMissileIter->data);
    }

    for(playerMissileIter=playerMissiles;playerMissileIter;playerMissileIter=playerMissileIter->next) {
      Missile_Draw(playerMissileIter->data);
    }

		for(explosionIter=explosions;explosionIter;explosionIter=explosionIter->next) {
      Explosion_Draw(explosionIter->data);
    }

		if(gameover) {
			glPrint(10,10,"GAMEOVER",GL2D_RGBA(0x00,0xFF,0x00,0xFF));
		}

		char scoreStr[256];
		sprintf(scoreStr,"%07d",score);
		glPrint(SCREEN_WIDTH-strlen(scoreStr)*10-10,10,scoreStr,GL2D_RGBA(0x00,0xFF,0x00,0xFF));


  glEnd2D();

}



int main(int argc,char **argv) {

  double fps;
  double dt=0;
  double accumulator=0;

  GLFWvidmode mode;
  int windowWidth,windowHeight;

	int i;



  srand(time(NULL));

  glfwInit();
  glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE,GL_TRUE);
  glScreen2D(SCREEN_WIDTH,SCREEN_HEIGHT,GLFW_WINDOW);
  glfwSetWindowTitle(GAME_TITLE);
  glfwGetDesktopMode(&mode);
  glfwGetWindowSize(&windowWidth,&windowHeight);
  glfwSetWindowPos((mode.Width-windowWidth)/2,(mode.Height-windowHeight)/2);
  glfwSwapInterval(0);

  playerTurret=Turret_New(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,turretRadius,turretHeading,turretLifeMax,GL2D_RGBA(0x00,0xFF,0x00,0xFF),GL2D_RGBA(0x00,0x80,0x00,0xFF));

	for(i=0;i<6;i++) {
		double radius=25;
		double x=radius*cos(radians((double)i/6*360))+SCREEN_WIDTH/2;
		double y=radius*sin(radians((double)i/6*360))+SCREEN_HEIGHT/2;
		List_Push(&buildings,Building_New(x,y,buildingRadius,buildingLifeMax,GL2D_RGBA(0x00,0xFF,0x00,0xFF),GL2D_RGBA(0x00,0x80,0x00,0xFF)),Building_Delete);
		numBuildings++;
	}
	for(i=0;i<12;i++) {
		double radius=50;
		double x=radius*cos(radians((double)i/12*360))+SCREEN_WIDTH/2;
		double y=radius*sin(radians((double)i/12*360))+SCREEN_HEIGHT/2;
		List_Push(&buildings,Building_New(x,y,buildingRadius,buildingLifeMax,GL2D_RGBA(0x00,0xFF,0x00,0xFF),GL2D_RGBA(0x00,0x80,0x00,0xFF)),Building_Delete);
		numBuildings++;
	}
	for(i=0;i<18;i++) {
		double radius=75;
		double x=radius*cos(radians((double)i/18*360))+SCREEN_WIDTH/2;
		double y=radius*sin(radians((double)i/18*360))+SCREEN_HEIGHT/2;
		List_Push(&buildings,Building_New(x,y,buildingRadius,buildingLifeMax,GL2D_RGBA(0x00,0xFF,0x00,0xFF),GL2D_RGBA(0x00,0x80,0x00,0xFF)),Building_Delete);
		numBuildings++;
	}


  while(!quit) {
    dt=getDeltaTime(&fps,glfwGetTime());
    if(dt>FIXED_TIME_STEP) dt=FIXED_TIME_STEP;
    accumulator+=dt;
    while(accumulator>=FIXED_TIME_STEP)
    {
      update();
      accumulator-=FIXED_TIME_STEP;
    }

    glClearScreen();
    glLineWidth(5);
    glEnableAntialias( true );
    draw();
    glfwSleep(0.0000001);
    glfwSwapBuffers();

    quit=glfwGetKey(GLFW_KEY_ESC)|!glfwGetWindowParam(GLFW_OPENED);
  }

  Turret_Delete(playerTurret);
  List_Clear(&playerMissiles);
  List_Clear(&enemyMissiles);
  List_Clear(&explosions);

  glClose();
	glfwTerminate();

  return 0;
}
