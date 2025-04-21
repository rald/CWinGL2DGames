#ifndef TURRET_H
#define TURRET_H

#include <stdlib.h>

#include "GL/gl2d.h"

extern int mouseX,mouseY;

typedef struct Turret Turret;
struct Turret {
  double x1,y1,x2,y2;
  double radius;
  double heading;
  double life,lifeMax;
  GLuint stroke,fill;
};

Turret *Turret_New(double x,double y,double radius,double heading,double lifeMax,GLuint stroke,GLuint fill);
void Turret_Update(Turret *turret);
void Turret_Draw(Turret *turret);
void Turret_Delete(Turret *turret);

#endif
