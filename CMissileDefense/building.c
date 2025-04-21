#include "building.h"

Building *Building_New(double x,double y,double radius,double lifeMax,GLuint stroke,GLuint fill) {
  Building *building=malloc(sizeof(*building));
  if(building) {
    building->x=x;
    building->y=y;
    building->radius=radius;
    building->lifeMax=lifeMax;
    building->life=lifeMax;
    building->stroke=stroke;
    building->fill=fill;
  }
  return building;
}

void Building_Draw(Building *building) {
  double radius=building->life/building->lifeMax*building->radius;
  glEllipseFilled(building->x,building->y,radius,radius,0,building->fill);
  glEllipse(building->x,building->y,building->radius,building->radius,0,building->stroke);
}

void Building_Delete(void *building) {
  free((Building*)building);
  building=NULL;
}
