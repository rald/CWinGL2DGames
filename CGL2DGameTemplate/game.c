#include "GL/glfw.h"
#include "GL/gl2d.h"

#include <stdbool.h>
#include <math.h>


#define GAME_TITLE "CGL2DGameTemplate"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480



int main(int argc, char *argv[]) {

	double timeStart=0;
	bool quit=false;

	double cx=SCREEN_WIDTH/2,cy=SCREEN_HEIGHT/2;
	double x[3],y[3];
	int frame=0;



	glScreenInit(SCREEN_WIDTH,SCREEN_HEIGHT);

	glfwSetWindowTitle(GAME_TITLE);


	glfwSwapInterval(1);


	glBlendMode(GL2D_ALPHA);

	while(!quit) {

		x[0]=cos((double)frame/7)*150+cx;
		y[0]=sin((double)frame/11)*100+cy;

		x[1]=cos((double)frame/11)*100+cx;
		y[1]=sin((double)frame/7)*150+cy;

		x[2]=cos((double)frame/13)*200+cx;
		y[2]=sin((double)frame/17)*150+cy;

		glBoxFilled(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,GL2D_RGBA(0,0,0,8));

		glEllipseFilled(x[0],y[0],25,25,0,GL2D_RGBA(255,0,0,255));
		glEllipseFilled(x[1],y[1],25,25,0,GL2D_RGBA(0,255,0,255));
		glEllipseFilled(x[2],y[2],25,25,0,GL2D_RGBA(0,0,255,255));

		glLine(0,0,50,50,GL2D_RGBA(255,255,255,255));

		glBox(75,0,125,50,GL2D_RGBA(255,255,255,255));

		glEllipse(175,25,25,25,0,GL2D_RGBA(255,255,255,255));

		glBoxFilled(225,0,275,50,GL2D_RGBA(255,255,255,255));

		glEllipseFilled(325,25,25,25,0,GL2D_RGBA(255,255,255,255));

		char str[256];

		frame++;



		glfwSwapBuffers();

		timeStart = glfwGetTime();
		while(glfwGetTime()-timeStart < 1.0/60.0) {};

		quit = glfwGetKey(GLFW_KEY_ESC) | !glfwGetWindowParam(GLFW_OPENED);

	}

	glfwTerminate();

	return 0;
}
