#include "common.h"
#include "player.h"
#include "bubble.h"
#include "harpoon.h"

double drand() {
	return rand()/(RAND_MAX+1.0);
} 

double sgn(double x) {
	return x<0?-1:(x>0?1:0);
}

bool hitcircrect(
		double cx, double cy, double radius, 
		double rx, double ry, double rw, double rh) {

  // temporary variables to set edges for testing
  double testX = cx;
  double testY = cy;

  // which edge is closest?
  if (cx < rx)         testX = rx;      // test left edge
  else if (cx > rx+rw) testX = rx+rw;   // right edge
  if (cy < ry)         testY = ry;      // top edge
  else if (cy > ry+rh) testY = ry+rh;   // bottom edge

  // get distance from closest edges
  double distX = cx-testX;
  double distY = cy-testY;
  double distance = sqrt( (distX*distX) + (distY*distY) );

  // if the distance is less than the radius, collision!
  if (distance <= radius) {
    return true;
  }
  return false;
}

bool hitrectrect(double r1x, double r1y, double r1w, double r1h, double r2x, double r2y, double r2w, double r2h) {
  if (r1x + r1w >= r2x &&
      r1x <= r2x + r2w &&
      r1y + r1h >= r2y &&
      r1y <= r2y + r2h) {
        return true;
  }
  return false;
}

int main() {

	bool quit=false;

	glImage playerImage;
	glImage bubbleImages[4];
	glImage harpoonImages[2];

	GLuint playerTexture;
	GLuint bubbleTextures[4];
	GLuint harpoonTextures[2];

	srand(time(NULL));

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);
	glfwSetWindowTitle(GAME_TITLE);
	glfwSwapInterval(1);

	playerTexture=glLoadSprite(
			"images/player.tga",
			&playerImage,
			16,32,
			GL_NEAREST);

	bubbleTextures[0]=glLoadSprite(
			"images/bubble8x8.tga",
			&bubbleImages[0],
			8,8,
			GL_NEAREST);

	bubbleTextures[1]=glLoadSprite(
			"images/bubble16x16.tga",
			&bubbleImages[1],
			16,16,
			GL_NEAREST);

	bubbleTextures[2]=glLoadSprite(
			"images/bubble32x32.tga",
			&bubbleImages[2],
			32,32,
			GL_NEAREST);

	bubbleTextures[3]=glLoadSprite(
			"images/bubble64x64.tga",
			&bubbleImages[3],
			64,64,
			GL_NEAREST);

	harpoonTextures[0]=glLoadSprite(
			"images/spear.tga",
			&harpoonImages[0],
			16,16,
			GL_NEAREST);

	harpoonTextures[1]=glLoadSprite(
			"images/rope.tga",
			&harpoonImages[1],
			16,16,
			GL_NEAREST);

	Player *player=Player_New(
			playerImage,
			(SCREEN_WIDTH-playerImage.width)/2,
			SCREEN_HEIGHT-playerImage.height,
			4);

	Bubble *bubbles[BUBBLES_MAX];
	int numBubbles=0;

	Harpoon *harpoon=NULL;

	int bubbleSpawnCounter=0;

	while(!quit) {

    glClearColor( 0xCA/255.0f, 0xDC/255.0f, 0x9F/255.0f, 0xFF/255.0f );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		bubbleSpawnCounter++;
		if(bubbleSpawnCounter>=600) {
			bubbleSpawnCounter=0;
			if(numBubbles<BUBBLES_MAX) {
				bubbles[numBubbles]=Bubble_New(
						bubbleImages,
						rand()%(SCREEN_WIDTH-bubbleImages[3].width),
						0,
						3,
						(rand()%2?1:-1)*drand(),
						(rand()%2?1:-1)*drand());
				numBubbles++;
			}
		}


		for(int i=0;i<numBubbles;i++) {
			Bubble_Update(bubbles[i]);
		}
		
		Player_Update(player);

		if(player->state==PLAYER_STATE_FIRING) {
			if(!harpoon) {
				harpoon=Harpoon_New(
						harpoonImages,
						(player->image.width-harpoonImages[0].width)/2+player->x,
						(player->image.height)+player->y,
						4);
			}
		}

		if(harpoon) {
			Harpoon_Update(harpoon);
			if(harpoon->y<=0) {
				player->canFire=true;
				Harpoon_Delete(&harpoon);
			} else { 
			
				for(int i=0;i<numBubbles;i++) {
				
					if(hitrectrect(
							bubbles[i]->x,
							bubbles[i]->y,
							bubbles[i]->images[bubbles[i]->size].width,
							bubbles[i]->images[bubbles[i]->size].height,
							harpoon->x,
							harpoon->y,
							harpoon->images[1].width,
							SCREEN_HEIGHT-harpoon->y)) {
					
						player->canFire=true;
						Harpoon_Delete(&harpoon);

						if(bubbles[i]->size>0) {
							if(numBubbles<BUBBLES_MAX) {
								bubbles[i]->size--;
								bubbles[numBubbles]=Bubble_New(
									bubbleImages,
									bubbles[i]->x-8,
									bubbles[i]->y,
									bubbles[i]->size,
									bubbles[i]->vx,
									bubbles[i]->vy
								);

								bubbles[numBubbles]->dx=-fabs(bubbles[i]->dx);
								bubbles[numBubbles]->dy=bubbles[i]->dy;
								numBubbles++;
								bubbles[i]->x+=8;
								bubbles[i]->dx=fabs(bubbles[i]->dx);
								break;
							}
						} else {
							Bubble_Delete(&bubbles[i]);
							for(int j=i;j<numBubbles-1;j++) {
								bubbles[j]=bubbles[j+1];
							}
							numBubbles--;
							break;
						}

					}
				}
			}
		}

		for(int i=0;i<numBubbles;i++) {
			Bubble_Draw(bubbles[i]);	
		}


		Player_Draw(player);			

		if(harpoon) {
			Harpoon_Draw(harpoon);
		}

		float TimeStart=glfwGetTime();
		while((glfwGetTime()-TimeStart)<(1.0/100.0)){};
	
		glfwSwapBuffers();
	
		quit=glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);
	}
	
	if(harpoon) Harpoon_Delete(&harpoon);

	for(int i=0;i<numBubbles;i++) {
		Bubble_Delete(&bubbles[i]);
	}

	Player_Delete(&player);


	glDeleteTextures(1,&playerTexture);
	glDeleteTextures(4,bubbleTextures);
	glDeleteTextures(2,harpoonTextures);

	glfwTerminate();

	return 0;
}
