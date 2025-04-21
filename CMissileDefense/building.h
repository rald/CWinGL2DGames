#ifndef BUILDING_H
#define BUILDING_H

#include <stdlib.h>
#include <math.h>

#include "gl2d.h"

typedef struct Building Building;
struct Building {
  double x,y;
  double radius;
  double life,lifeMax;
  GLuint stroke,fill;
};

Building *Building_New(double x,double y,double radius,double life,GLuint stroke,GLuint fill);
void Building_Draw(Building *building);
void Building_Delete(void *building);

#endif
