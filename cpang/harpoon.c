#include "harpoon.h"

Harpoon *Harpoon_New(glImage *images,double x,double y,double speed) {
	Harpoon *harpoon=malloc(sizeof(Harpoon));
	if(harpoon) {
		harpoon->images=images;
		harpoon->x=x;
		harpoon->y=y;
		harpoon->speed=speed;
	}
	return harpoon;
}

void Harpoon_Delete(Harpoon **harpoon) {
	free(*harpoon);
	*harpoon=NULL;
}

void Harpoon_Draw(Harpoon *harpoon) {

	glSprite(harpoon->x,harpoon->y,GL2D_FLIP_NONE,&harpoon->images[0]);

	double y=harpoon->y+16;
	while(y<SCREEN_HEIGHT) {
		glSprite(harpoon->x,y,GL2D_FLIP_NONE,&harpoon->images[1]);
		y+=16;
	}

}

void Harpoon_Update(Harpoon *harpoon) {
	harpoon->y-=harpoon->speed;
	if(harpoon->y<0) {
		harpoon->y=0;
	}
}
