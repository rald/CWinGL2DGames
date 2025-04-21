#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include <GL/glfw.h>
#include <GL/gl2d.h>

#define GAME_TITLE "CGameOfLife" 

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[]) {

	int quit = 0;
	
	int cellSize=8;
	int worldWidth=SCREEN_WIDTH/cellSize;
	int worldHeight=SCREEN_HEIGHT/cellSize;
	bool world[worldHeight][worldWidth];
	bool life[worldHeight][worldWidth];

	int i,j,k,l;
	int x,y;
	int n;
	bool isAlive;
	bool isPlaying=false;
	bool isMouseButtonLeftHold=false;
	bool initial;
	
	int mouseX,mouseY;

	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);

	glfwSetWindowTitle(GAME_TITLE);

	glfwSwapInterval(1);

	for(j=0;j<worldHeight;j++) {
		for(i=0;i<worldWidth;i++) {
			world[j][i]=false;
			life[j][i]=false;
		}
	}

	glClearScreen();
	
	for(j=0;j<worldHeight;j++) {
		for(i=0;i<worldWidth;i++) {
			x=i*cellSize;
			y=j*cellSize;
			glBoxFilled(x,y,x+cellSize,y+cellSize,GL2D_RGBA(0x00,0x00,0x00,0xFF));				
			glBox(x,y,x+cellSize,y+cellSize,GL2D_RGBA(0x50,0x50,0x50,0xFF));
		}
	}

	while(!quit) {
		
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS) {
			glfwGetMousePos(&mouseX,&mouseY);
			x=mouseX/cellSize;
			y=mouseY/cellSize;
			if(!isMouseButtonLeftHold) {
				if(x>=0 && x<worldWidth && y>=0 && y<worldHeight) {
					initial=world[y][x];
					isMouseButtonLeftHold=true;
				}
			} else {
				if(x>=0 && x<worldWidth && y>=0 && y<worldHeight) {
					world[y][x]=!initial;
					glBoxFilled(
							x*cellSize+1,
							y*cellSize+1,
							x*cellSize+cellSize-1,
							y*cellSize+cellSize-1,
							world[y][x]?
									GL2D_RGBA(0xFF,0xFF,0xFF,0xFF):
									GL2D_RGBA(0x00,0x00,0x00,0xFF));				
				}
			}
		} else {
			if(isMouseButtonLeftHold) isMouseButtonLeftHold=false;
		}
				
		if(glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS) {
			isPlaying=true;
		} else {
			isPlaying=false;
		}

		if(isPlaying) {
		
			for(y=0;y<worldHeight;y++) {
				for(x=0;x<worldWidth;x++) {

					isAlive=world[y][x];
					
					n=0;
					for(j=-1;j<=1;j++) {
						for(i=-1;i<=1;i++) {
							if(i!=0 || j!=0) {
								k=x+i;
								l=y+j;
								if(k<0) k=worldWidth-1;
								if(k>worldWidth-1) k=0; 
								if(l<0) l=worldHeight-1;
								if(l>worldHeight-1) l=0;
								if(world[l][k]) n++;
							}
						}
					}
				
					if(isAlive) {
						if(n>=4 || n<=1) {
							life[y][x]=false;
						}	else if(n==2 || n==3) {
							life[y][x]=true;
						}
					} else {
						if(n==3) life[y][x]=true;
					}
					
				
				}
			}
			
			for(y=0;y<worldHeight;y++) {
				for(x=0;x<worldWidth;x++) {
					world[y][x]=life[y][x];
					glBoxFilled(
							x*cellSize+1,
							y*cellSize+1,
							x*cellSize+cellSize-1,
							y*cellSize+cellSize-1,
							world[y][x]?
									GL2D_RGBA(0xFF,0xFF,0xFF,0xFF):
									GL2D_RGBA(0x00,0x00,0x00,0xFF));				
				}
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

