#include "bubble.h"

Bubble *Bubble_New(glImage *images,double x,double y,int size,double vx,double vy) {
	Bubble *bubble=malloc(sizeof(Bubble));

	if(bubble) {
		bubble->images=images;
		bubble->x=x;
		bubble->y=y;
		bubble->size=size;
		bubble->vx=vx;
		bubble->vy=vy;
		bubble->dx=vx;
		bubble->dy=vy;
		bubble->g=GRAVITY;
	}

	return bubble;
}

void Bubble_Delete(Bubble **bubble) {
	free(*bubble);
	*bubble=NULL;
}

void Bubble_Draw(Bubble *bubble) {
	glSprite(bubble->x,bubble->y,GL2D_FLIP_NONE,&bubble->images[bubble->size]);
}

void Bubble_Update(Bubble *bubble) {

	bubble->dy+=bubble->g;

	bubble->x+=bubble->dx;
	bubble->y+=bubble->dy;

	if(bubble->x<0) {
		bubble->x=0;
		bubble->dx=fabs(bubble->dx);
	}

	if(bubble->y<0) {
		bubble->y=0;
		bubble->dy=fabs(bubble->dy);
	}

	if(bubble->x>SCREEN_WIDTH-bubble->images[bubble->size].width) {
		bubble->x=SCREEN_WIDTH-bubble->images[bubble->size].width;
		bubble->dx=-fabs(bubble->dx);
	}

	if(bubble->y>SCREEN_HEIGHT-bubble->images[bubble->size].height) {
		bubble->y=SCREEN_HEIGHT-bubble->images[bubble->size].height;
		bubble->dy=-fabs(bubble->dy);
	}

}

