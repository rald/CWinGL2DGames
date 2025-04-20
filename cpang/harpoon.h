#ifndef HARPOON_H
#define HARPOON_H

#include "common.h"
#include "player.h"

typedef struct Harpoon Harpoon;

struct Harpoon {
	glImage *images;
	double x,y;
	double speed;
};

Harpoon *Harpoon_New(glImage *images,double x,double y,double speed);
void Harpoon_Delete(Harpoon **harpoon);
void Harpoon_Draw(Harpoon *harpoon);
void Harpoon_Update(Harpoon *harpoon);

#endif
